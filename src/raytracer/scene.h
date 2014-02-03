#ifndef __SCENE_H__
#define __SCENE_H__

#include "object.h"
#include "sphere.h"
#include "plane.h"
#include "intersection.h"
#include "camera.h"

class Scene {
    public :
        Scene(Camera &cam);
        ~Scene();

        bool Intersect(const Ray &ray, Intersection *isect) const;
        void AddObject(Object* object);
        const Camera& SceneCamera() const;

    private:
        Camera camera;
        vector<Object*> *objects;
};

#endif
