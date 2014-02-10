#include "renderer.h"

void Renderer::Render(Scene *scene, const Vec2 &size) {
    NetPBMLoader loader;

    int width = size.x;
    int height = size.y;

    float pxw = 1.0 / (float) width;
    float pxh = 1.0 / (float) height;

    PPMImage img(width, height);

    for(int x = 0; x < width; ++x) {
        float xval = x / (float) width;
        fprintf(stdout, "\rRendering %5.2f%%", 100.0 * (x / (float) width));
        for(int y = 0; y < height; ++y) {
            float yval = y / (float) height;
            Color c;

            for(int s = 0; s < sppxl; ++s) 
                c += AverageColor(scene, xval, yval, pxw, pxh, 0);
            img(x, y) = (c / (float) sppxl) * 255.0; 
        }
    }
    cout << endl;

    loader.SavePPM(img, "image");
}

Color Renderer::AverageColor(Scene *scene, float x, float y, float pxw, float pxh, int aadepth) const {
    Camera cam = scene->SceneCamera();

    if(aadepth == AA_MAX_DEPTH) {
        if(sppxl > 1) {
            x += (float) rand() / RAND_MAX * pxw - pxw / 2.0;   
            y += (float) rand() / RAND_MAX * pxh - pxh / 2.0;
        }
        return Ri(scene, cam.PrimaryRay(Vec2(x, y)), 0, Vec2(x, y));
    }
    
    Color c;

    c += AverageColor(scene, x - pxw / 2.0, y - pxh / 2.0, pxw / 2.0, pxh / 2.0, aadepth + 1);
    c += AverageColor(scene, x + pxw / 2.0, y - pxh / 2.0, pxw / 2.0, pxh / 2.0, aadepth + 1);
    c += AverageColor(scene, x - pxw / 2.0, y + pxh / 2.0, pxw / 2.0, pxh / 2.0, aadepth + 1);
    c += AverageColor(scene, x + pxw / 2.0, y + pxh / 2.0, pxw / 2.0, pxh / 2.0, aadepth + 1);

    return c / 4.0;
}

Color Renderer::Ri(Scene *scene, const Ray& ray, int depth, const Vec2 &pixelPos, Object *caller) const {
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
