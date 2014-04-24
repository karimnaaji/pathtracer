#include "scene.h"

Scene::Scene(Camera *cam) 
    : camera(cam) {
    objects = new vector<Object*>();
    lights = new vector<Object*>();
}

Scene::Scene() {
    objects = new vector<Object*>();
    lights = new vector<Object*>();
}

Scene::~Scene() {
    vector<Object*>::iterator it;
    for(it = objects->begin(); it != objects->end(); ++it) 
        delete *it;
    delete objects;
    delete lights;
    delete camera;
}

void Scene::AddObject(Object* object) {
    if(object->Emit()) {
        lights->push_back(object);
    }
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

unsigned int Scene::ObjectsCount() const {
    return objects->size();
}

vector<const Object*> Scene::Lights() const {
    vector<const Object*> lghts(lights->cbegin(), lights->cend());
    return lghts;
}
