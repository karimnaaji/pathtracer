#ifndef __RENDERER_H__
#define __RENDERER_H_

#include <thread>
#include <mutex>

#include "renderingtask.h"
#include "scene.h"

class Renderer {
    public:
        Renderer(int samples = 1);
        ~Renderer();
        void Init(const PPMImage &film);
        void Render(Scene *scene);

    private:
        vector<RenderingTask*> *tasks;
        int sppxl;
        mutex *mtx;
};

#endif
