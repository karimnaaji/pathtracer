#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "object.h"

class Triangle : public Object {
    public:
        Triangle(Vec3 pt1, Vec3 pt2, Vec3 pt3, Vec3 pos, Vec3 col, Vec3 emis) 
            : Object(pos, col, emis), p1(pt1), p2(pt2), p3(pt3) {}
        ~Triangle() {}
        bool Intersect(const Ray &ray, Intersection *isect);
        string Description() const;
        Vec3 Normal(Vec3 p) const;

    private:
        Vec3 p1, p2, p3;
        Vec3 n;
};

#endif
