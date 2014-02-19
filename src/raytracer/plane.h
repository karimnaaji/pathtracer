#ifndef __PLANE_H__
#define __PLANE_H__

#include "object.h"

class Plane : public Object {
    public:
        Plane(Vec3 p, Vec3 col, Vec3 emis) : Object(p, col, emis) {}
        ~Plane() {}
        bool Intersect(const Ray &ray, Intersection *isect);
        string Description() const;
        Vec3 Normal(Vec3 p, Vec3 dir) const;
};

#endif
