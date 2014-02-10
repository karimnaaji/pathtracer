#ifndef __SCENE_H__
#define __SCENE_H__

#include "object.h"
#include "sphere.h"
#include "plane.h"
#include "intersection.h"
#include "camera.h"

class Scene {
    public :
        Scene();
        Scene(Camera &cam);
        ~Scene();

        bool Intersect(const Ray &ray, Intersection *isect, Object *caller) const;
        void AddObject(Object* object);
        void SetCamera(const Camera &cam) { camera = cam; }
        const Camera& SceneCamera() const;

    private:
        Camera camera;
        vector<Object*> *objects;
};

#endif
