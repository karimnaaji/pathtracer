#include "renderer.h"

Renderer::Renderer(int samples) : sppxl(samples) {
    mtx = new mutex();
    tasks = new vector<RenderingTask*>();
}

void Renderer::Init(const PPMImage &film) {
    int width = film.GetWidth();
    int height = film.GetHeight();
    int bwidth = film.GetWidth() / 18;
    int bheight = film.GetHeight() / 18;
    int id = 0;

    for(int x = 0; x < width; x += bwidth) {
        int minx = x;
        int maxx = x + bwidth > width ? width : x + bwidth;
        for(int y = 0; y < height; y += bheight) {
            int miny = y;
            int maxy = y + bheight > height ? height : y + bheight;

            // create the new rendering task
            Bucket *bucket = new Bucket(minx, miny, maxx, maxy);
            RenderingTask *rt = new RenderingTask(bucket, sppxl, Vec2(width, height), ++id, mtx);
            tasks->push_back(rt);
        }
    }

    cout << "Initialized " << tasks->size() << " rendering tasks" << endl;
}

Renderer::~Renderer() {
    vector<RenderingTask*>::iterator it;
    for(it = tasks->begin(); it != tasks->end(); it++) 
        delete *it;
    delete tasks;
    delete mtx;
}

void Renderer::Render(Scene *scene) {
    thread *threads = new thread[tasks->size()];
    int *progress = new int();

    *progress = 0;

    for(unsigned int i = 0; i < tasks->size(); ++i) {
        RenderingTask *task = (*tasks)[i];
        threads[i] = thread(&RenderingTask::Start, task, scene, progress);
    }

    // start threads
    for(unsigned int i = 0; i < tasks->size(); ++i) {
        threads[i].join();
    }

    cout << endl;

    delete[] threads;
    delete progress;
}
