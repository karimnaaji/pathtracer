#ifndef __SCENE_H__
#define __SCENE_H__

#include "camera.h"
#include "object.h"
#include "config.h"

class Scene {
    public :
        Scene();
        Scene(Camera *cam);
        ~Scene();

        bool Intersect(const Ray &ray, Intersection *isect, Object *caller) const;
        void AddObject(Object* object);
        void SetCamera(Camera *cam) { camera = cam; }
        Camera* GetCamera() const { return camera; }
        vector<const Object*> Lights() const;
        unsigned int ObjectsCount() const;

    private:
        Camera *camera;
        vector<Object*> *objects;
        vector<Object*> *lights;
};

#endif
