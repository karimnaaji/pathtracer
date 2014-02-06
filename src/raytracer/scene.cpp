#include "scene.h"

Scene::Scene(Camera &cam) 
    : camera(cam) {
    objects = new vector<Object*>();
}

Scene::~Scene() {
    vector<Object*>::iterator it;
    for(it = objects->begin(); it != objects->end(); ++it) 
        delete *it;
    delete objects;
}

void Scene::AddObject(Object* object) {
    objects->push_back(object);
}

bool Scene::Intersect(const Ray& ray, Intersection *isect, Object *caller) const {
    bool hit = false;

    for(vector<Object*>::iterator it = objects->begin(); it != objects->end(); ++it) {
        if(*it == caller) continue;
        hit |= (*it)->Intersect(ray, isect);
        if(!hit) isect->obj = NULL;
    }

    return hit;
}

const Camera& Scene::SceneCamera() const {
    return camera;
}
