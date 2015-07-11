#include "renderingtask.h"

RenderingTask::~RenderingTask() {
    delete bucket;
}

void RenderingTask::Start(Scene* scene, int *progress) {
    PPMImage *film = scene->GetCamera()->Film();

    int width = film->GetWidth();
    int height = film->GetHeight();
    float n = (float) width * height;

    float pxw = 1.0 / (float) width;
    float pxh = 1.0 / (float) height;
    float gamma = 2.2;

    for(int x = bucket->minx; x < bucket->maxx; ++x) {
        float xval = x / (float) width;
        for(int y = bucket->miny; y < bucket->maxy; ++y) {
            float yval = y / (float) height;
            Color c;

            for(int s = 0; s < sppxl; ++s) 
                c += AverageColor(scene, xval, yval, pxw, pxh, 0, sppxl);
            c = (c / (float) sppxl); 
            // gamma correction
            c = Vec3(pow(c.r, 1.0 / gamma), pow(c.g, 1.0 / gamma), pow(c.b, 1.0 / gamma));

            (*film)(x, y) = Color::VClamp(c, 0.0, 1.0) * 255.0;
            *progress = *progress + 1;
        }
        mtx->lock();
        fprintf(stdout, "\rProgress %5.2f%%", 100.0 * (float)*progress / n);
        mtx->unlock();
    }
}
