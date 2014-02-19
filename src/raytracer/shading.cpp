#include "shading.h"

Color AverageColor(Scene *scene, float x, float y, float pxw, float pxh, int aadepth, int sppxl) {
    Camera *cam = scene->GetCamera();

    if(aadepth == AA_MAX_DEPTH) {
        if(sppxl > 1) {
            x += rand_0_1() * pxw - pxw / 2.0;   
            y += rand_0_1() * pxh - pxh / 2.0;
        }
        return Ri(scene, cam->PrimaryRay(Vec2(x, y)), 0, Vec2(x, y));
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
        return Vec3(0.1); //Vec3::Zero();
    } 

    Object *obj = isect.obj;
    Color c = obj->color; 

    if(depth > 20) {
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
            }
            break;
    }

    return obj->emission + c;
}
