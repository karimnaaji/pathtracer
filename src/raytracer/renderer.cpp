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
            Vec3 rd = cam.GetRight() * p.x + cam.GetUp() * p.y + cam.GetDir();
            Vec3 col = Vec3::Zero();

            rd = rd.Normalize();
            Intersection* isect = new Intersection();
            isect->spos = Vec2(x, y);
            Ray r = Ray(cam.GetPos(), rd);

            if(scene->Intersect(r, isect)) {
                if(isect->t > 0.0) {
                    Object *obj = isect->obj;
                    col = obj->color * Vec3::Abs(isect->n).y;
                }
            }

            delete isect;

            img(x, y) = col;
        }
    }

    loader.SavePPM(img, "image");
}
