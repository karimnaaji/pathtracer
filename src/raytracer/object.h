#ifndef __PRIMITIVE_H__
#define __PRIMITIVE_H__

#include "ray.h"
#include "intersection.h"
#include "material.h"
#include "raytracer.h"
#include "matrix4.h"

class Object {
    public:
        Object(Vec3 &pos, Vec3 &col, Vec3 &emis) :
            position(pos), color(col), emission(emis) { }
        virtual bool Intersect(const Ray &ray, Intersection *isect) = 0;
        virtual ~Object() { }

        Vec3 position;
        Vec3 color;
        Vec3 emission;
        MaterialType material;
        Matrix4 transform;
};

#endif
