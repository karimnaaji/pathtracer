#ifndef __RENDERING_TASK_H__
#define __RENDERING_TASK_H__

#include <mutex>

#include "config.h"
#include "shading.h"
#include "helpers.h"
#include "scene.h"

struct Bucket {
    Bucket(int mix, int miy, int max, int may) :
        minx(mix), miny(miy), maxx(max), maxy(may) {}
    int minx, miny;
    int maxx, maxy;
};

class RenderingTask {
    public:
        RenderingTask(Bucket* bckt, int samplesppx, Vec2 imgSize, int identitifier, mutex* mutx) 
            : bucket(bckt), sppxl(samplesppx), size(imgSize), id(identitifier), mtx(mutx) {}
        ~RenderingTask();
        void Start(Scene* scene, int *progress);

    private:
        Bucket *bucket;
        int sppxl;
        Vec2 size;
        int id;
        mutex *mtx;
};

#endif
