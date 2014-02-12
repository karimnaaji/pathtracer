#include "renderingtask.h"

RenderingTask::~RenderingTask() {
    delete bucket;
}

void RenderingTask::Start(Scene* scene, float *progress) {
    PPMImage *film = scene->GetCamera()->Film();

    int width = film->GetWidth();
    int height = film->GetHeight();

    float pxw = 1.0 / (float) width;
    float pxh = 1.0 / (float) height;
    
    for(int x = bucket->minx; x < bucket->maxx; ++x) {
        mtx->lock();
        *progress = 100.0 * (x - bucket->minx) / ((float) bucket->maxx - bucket->minx);
        fprintf(stdout, "\rAverage progress %5.2f%%", *progress);
        mtx->unlock();

        float xval = x / (float) width;
        for(int y = bucket->miny; y < bucket->maxy; ++y) {
            float yval = y / (float) height;
            Color c;

            for(int s = 0; s < sppxl; ++s) 
                c += AverageColor(scene, xval, yval, pxw, pxh, 0, sppxl);
            c = (c / (float) sppxl); 

            (*film)(x, y) = Color::VClamp(c, 0.0, 1.0) * 255.0;
        }
    }
}
