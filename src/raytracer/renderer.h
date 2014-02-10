#ifndef __RENDERER_H__
#define __RENDERER_H_

#include "scene.h"
#include "ray.h"
#include "netpbmloader.h"
#include "sphere.h"
#include "object.h"
#include "color.h"

#define AA_MAX_DEPTH 2

class Renderer {
    public:
        Renderer(int samples = 1) : sppxl(samples) {}
        void Render(Scene* scene, const Vec2 &size);
        Color Ri(Scene *scene, const Ray& ray, int depth, const Vec2 &pixelPos, Object *caller = NULL) const;
        Color AverageColor(Scene *scene, float x, float y, float pxw, float pxh, int depth) const;

        int sppxl;
};

#endif
