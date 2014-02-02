#ifndef __RENDERER_H__
#define __RENDERER_H_

#include "scene.h"
#include "ray.h"
#include "netpbmloader.h"
#include "sphere.h"
#include "object.h"

class Renderer {
    public:
        Renderer() {}
        void Render(const Scene* scene);
};

#endif
