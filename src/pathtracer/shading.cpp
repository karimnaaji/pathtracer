#include "shading.h"

Color AverageColor(Scene *scene, float x, float y, float pxw, float pxh, int aadepth, int sppxl) {
    Camera *cam = scene->GetCamera();

    if(aadepth == AA_MAX_DEPTH) {
        if(sppxl > 1) {
            x += rand_0_1() * pxw - pxw / 2.0;   
            y += rand_0_1() * pxh - pxh / 2.0;
        }

        Ray ray = cam->PrimaryRay(Vec2(x,y));
        float lensRadius = 0.1f;
        float focalDistance = 1.5f;

        if(lensRadius > 0.) {
            Intersection isect;
            float lensU = (2.0 * rand_0_1() - 1.0) * lensRadius;
            float lensV = (2.0 * rand_0_1() - 1.0) * lensRadius;
            scene->Intersect(ray, &isect, NULL);
            float ft = abs(focalDistance / isect.p.z);
            Vec3 focus = ray(ft);
            ray.o = Vec3(ray.o.x + lensU, ray.o.y + lensV, ray.o.z);
            ray.d = (ray.d + focus - ray.o).Normalize();
        }

        return Ri(scene, ray, 0, Vec2(x, y));
    }
    
    Color c;

    c += AverageColor(scene, x - pxw / 2.0, y - pxh / 2.0, pxw / 2.0, pxh / 2.0, aadepth + 1, sppxl);
    c += AverageColor(scene, x + pxw / 2.0, y - pxh / 2.0, pxw / 2.0, pxh / 2.0, aadepth + 1, sppxl);
    c += AverageColor(scene, x - pxw / 2.0, y + pxh / 2.0, pxw / 2.0, pxh / 2.0, aadepth + 1, sppxl);
    c += AverageColor(scene, x + pxw / 2.0, y + pxh / 2.0, pxw / 2.0, pxh / 2.0, aadepth + 1, sppxl);

    return c / 4.0;
}

Color Ri(Scene *scene, const Ray& ray, int depth, const Vec2 &pixelPos, Object *caller) {
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
                return obj->emission + c * Ri(scene, r, depth + 1, pixelPos, obj);
            }
            break;
        case E_SPECULAR:
            {
                Vec3 d = ray.d - 2.0 * isect.n * isect.n.Dot(ray.d);
                d.Normalize();
                Ray r = Ray(isect.p, d);
                return obj->emission + c * Ri(scene, r, depth + 1, pixelPos, obj);
            }
            break;
        case E_REFRACT:
            {
                Vec3 r = ray.d - 2.0 * isect.n * isect.n.Dot(ray.d);
                r.Normalize();
                Ray reflectRay = Ray(isect.p, r);

                bool in = ray.d.Dot(isect.n) < 0;
                float etat = 1.0;
                float etai = 1.33;

                if(in) {
                    Swap(etat, etai);
                }

                float eta = etai / etat;
                float cosi = isect.n.Dot(ray.d);
                float cost;
                float cos2i = cosi * cosi;
                float sint = (eta * eta) * (1 - cos2i);

                // total internal reflection
                if(sint >= 1) {
                    return obj->emission + c * Ri(scene, reflectRay, depth + 1, pixelPos, obj);
                }
    
                Vec3 t = eta * ray.d + (eta * cosi - sqrt(1 - sint)) * isect.n;
                t.Normalize();
                Ray refractRay = Ray(isect.p, t);
                cost = sqrt(1 - sint * sint);

                return obj->emission + c * Ri(scene, refractRay, depth + 1, pixelPos, obj);
            }
            break;
    }

    return obj->emission + c;
}
