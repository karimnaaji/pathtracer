#include "shading.h"

Color AverageColor(Scene *scene, float x, float y, float pxw, float pxh, int aadepth, int sppxl) {
    Camera *cam = scene->GetCamera();

    if(aadepth == AA_MAX_DEPTH) {
        if(sppxl > 1) {
            x += rand_0_1() * pxw - pxw / 2.0;   
            y += rand_0_1() * pxh - pxh / 2.0;
        }

        Ray ray = cam->PrimaryRay(Vec2(x,y));

        if(cam->getLensRadius() > 0.) {
            Intersection isect;
            Vec2 uv = cam->SampleLens();
            scene->Intersect(ray, &isect, NULL);
            float ft = abs(cam->getFocalDistance() / isect.p.z);
            Vec3 focus = ray(ft);
            ray.o = Vec3(ray.o.x + uv.x, ray.o.y + uv.y, ray.o.z);
            ray.d = (ray.d + focus - ray.o).Normalize();
        }

        return Shade(scene, ray, 0, Vec2(x, y));
    }
    
    Color c;

    c += AverageColor(scene, x - pxw / 2.0, y - pxh / 2.0, pxw / 2.0, pxh / 2.0, aadepth + 1, sppxl);
    c += AverageColor(scene, x + pxw / 2.0, y - pxh / 2.0, pxw / 2.0, pxh / 2.0, aadepth + 1, sppxl);
    c += AverageColor(scene, x - pxw / 2.0, y + pxh / 2.0, pxw / 2.0, pxh / 2.0, aadepth + 1, sppxl);
    c += AverageColor(scene, x + pxw / 2.0, y + pxh / 2.0, pxw / 2.0, pxh / 2.0, aadepth + 1, sppxl);

    return c / 4.0;
}

Color Shade(Scene *scene, const Ray& ray, int depth, const Vec2 &pixelPos, Object *caller) {
    Intersection isect;
    isect.spos = pixelPos;

    if(!scene->Intersect(ray, &isect, caller)) {
        // background color
        return Vec3::Zero();
    } 

    Object *obj = isect.obj;
    Color c = obj->color; 

    if(depth > 8) {
        return obj->emission;
    }

    switch(obj->material) {
        case E_DIFFUSE: 
            {
                float rdx, rdy, rdz;
                float magnitude;
                
                do {
                    rdx = 2.0 * rand_0_1() - 1.0;
                    rdy = 2.0 * rand_0_1() - 1.0;
                    rdz = 2.0 * rand_0_1() - 1.0;
                    magnitude = sqrt(rdx*rdx + rdy*rdy + rdz*rdz);
                } while(magnitude > 1.0);
                
                Vec3 d = Vec3(rdx / magnitude, rdy / magnitude, rdz / magnitude);
                if(d.Dot(isect.n) < 0.0) {
                    d = -d;
                }
                Ray r(isect.p, d);
                return obj->emission + c * Shade(scene, r, depth + 1, pixelPos, obj);
            }
            break;
        case E_SPECULAR:
            {
                Vec3 d = ray.d - 2.0 * isect.n * isect.n.Dot(ray.d);
                d.Normalize();
                Ray r = Ray(isect.p, d);
                return obj->emission + c * Shade(scene, r, depth + 1, pixelPos, obj);
            }
            break;
        case E_REFRACT:
            {
                bool into = ray.d.Dot(isect.n); 
                Vec3 n = isect.n;
                Vec3 nl = n.Dot(ray.d) < 0 ? n : n * -1;

                Ray newRay(isect.p, ray.d - n * 2 * n.Dot(ray.d));     

                float nc = 1;
                float nt = 1.5;
                float nnt = into ? nc / nt : nt / nc;
                float ddn = ray.d.Dot(nl);
                float cos2t = 1 - nnt * nnt * (1 - ddn * ddn);

                if (cos2t < 0) {
                    return obj->emission + c * Shade(scene, newRay, depth + 1, pixelPos, obj); 
                }

                Vec3 tdir = (ray.d * nnt - n * ((into ? 1 : - 1) * (ddn * nnt + sqrt(cos2t)))); 
                tdir.Normalize();

                float a = nt - nc;
                float b = nt + nc;
                float R0 = a * a / (b * b);
                float d = 1 - (into ? -ddn : tdir.Dot(n)); 
                float Re = R0 + (1 - R0) * d * d * d * d * d;
                float Tr = 1 - Re;

                if(depth > 2) {
                    float P = .25 + .5 * Re;
                    float r = rand_0_1();

                    if (r < P) {
                        float RP = Re / P;
                        return obj->emission + c * Shade(scene, newRay, depth + 1, pixelPos, obj) * RP;
                    } else {
                        float TP = Tr / (1 - P); 
                        return obj->emission + c * Shade(scene, Ray(isect.p, tdir), depth + 1, pixelPos, obj) * TP;
                    }
                } else {
                    return obj->emission + c * 
                       (Shade(scene, newRay, depth + 1, pixelPos, obj) * Re 
                      + Shade(scene, Ray(isect.p, tdir), depth + 1, pixelPos, obj) * Tr); 
                }
            }
            break;
    }

    return obj->emission + c;
}
