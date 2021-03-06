#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "object.h"

class Sphere : public Object {
    public:
        Sphere(Vec3 p, Vec3 col, Vec3 emis) : Object(p, col, emis) {}
        ~Sphere() {}
        bool Intersect(const Ray &ray, Intersection *isect);
        string Description() const;
        Vec3 Normal(Vec3 p, Vec3 dir) const;
        BBox Bounds() const;
};

#endif
