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
            }
            break;
        case E_SPECULAR:
            {
                Vec3 d = ray.d - 2.0 * isect.n * isect.n.Dot(ray.d);
                d.Normalize();
                Ray r = Ray(isect.p, d);
                return obj->emission + c * 0.99 * Ri(scene, r, depth + 1, pixelPos, obj);
            }
            break;
        case E_REFRACT:
            {
                Vec3 d = ray.d - 2.0 * isect.n * isect.n.Dot(ray.d);

            }
            break;
    }

    return obj->emission + c * Clamp(isect.n.y, 0.2, 1.0);
}
