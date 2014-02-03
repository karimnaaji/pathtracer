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
        virtual ostream& Description(ostream& o) const = 0;
        Vec3 virtual Normal(Vec3 p) const = 0;

        void FillIntersection(Intersection* isect, float t, const Ray& ray) {
            isect->t = t;
            isect->obj = this;
            isect->p = ray(t);
            isect->n = Normal(ray(t));
        }

        Vec3 position;
        Vec3 color;
        Vec3 emission;
        MaterialType material;
        Matrix4 transform;

		inline friend ostream& operator<<(ostream& o, const Object& obj) {
            return obj.Description(o);
        }
};

#endif
