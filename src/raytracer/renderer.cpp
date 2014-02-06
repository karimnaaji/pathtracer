#include "renderer.h"

void Renderer::Render(const Scene *scene) {
    NetPBMLoader loader;

    int width = 800;
    int height = 600;

    PPMImage img(width, height);

    Camera cam = scene->SceneCamera();

    for(int x = 0; x < width; ++x) {
        float xval = x / (float) width;
        for(int y = 0; y < height; ++y) {
            float yval = y / (float) height;
            Vec2 uv = Vec2(xval, yval);
            Vec2 p = -2.0f * uv + 1.0f; 
            Vec3 rd = (cam.GetRight() * p.x + cam.GetUp() * p.y + cam.GetDir()).Normalize();
            Ray r = Ray(cam.GetPos(), rd);
            Vec3 col = Ri(scene, r, 0, Vec2(x, y));

            img(x, y) = col * 255.0f;
        }
    }

    loader.SavePPM(img, "image");
}

Vec3 Renderer::Ri(const Scene *scene, const Ray& ray, int depth, const Vec2 &pixelPos, Object *caller) const {
    Intersection isect;
    isect.spos = pixelPos;

    if(depth > 0 && isect.spos.x == 200 && isect.spos.y == 260) {
        cout << "ray " << ray << endl;
    }

    if(!scene->Intersect(ray, &isect, caller)) {
        // background color
        return Vec3::Zero();
    } 

    Object *obj = isect.obj;
    Vec3 c = obj->color; 

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
                        
                /*cout << endl;
                cout << "depth: " << depth << endl;
                cout << "o ray: " << ray << endl;
                cout << "ray(isect.t)" << ray(isect.t) << endl;
                cout << r << endl;
                cout << *obj << endl;
                cout << isect << endl;
                cout << endl;*/

                return obj->emission + c * 0.99 * Ri(scene, r, depth + 1, pixelPos, obj);
            }
            break;
        case E_REFRACT:
            {
            }
            break;
    }

    return obj->emission + c * Clamp(isect.n.y, 0.2, 1.0);
}
