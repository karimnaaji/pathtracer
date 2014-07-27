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

    if(depth > 5) {
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
                bool into = ray.d.Dot(isect.n); // entering into the medium?

                float n1 = 1.0;
                float n2 = 1.5;

                float n1n2 = into ? (n1 / n2) : (n2 / n1);
                float n1n22 = n1n2 * n1n2;
                Vec3 n = into ? isect.n : -isect.n;
                Vec3 r = ray.d;
                float rn = r.Dot(n);
                float a = 1 - n1n22 * (1 - rn*rn);

                Ray refractRay;

                if(a >= 0) {
                    Vec3 d = r * n1n2 - n * (n1n2 * rn + sqrt(a));
                    refractRay = Ray(ray.o, d);
                } else {
                    refractRay = ray; // total internal reflection
                }

                return obj->emission + c * Shade(scene, refractRay, depth + 1, pixelPos, obj);
            }
            break;
    }

    return obj->emission + c;
}
