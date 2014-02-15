#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "triangle.h"

class Triangle : public Object {
    public:
        Triangle(Vec3 p1, Vec3 p2, Vec3 p3, Vec3 pos, Vec3 col, Vec3 emis) : Object(p, col, emis) {}
        ~Triangle() {}
        bool Intersect(const Ray &ray, Intersection *isect);
        string Description() const;
        Vec3 Normal(Vec3 p) const;
};

#endif
