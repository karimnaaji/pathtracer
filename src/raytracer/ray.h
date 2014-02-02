#ifndef __RAY_H__
#define __RAY_H__

#include "raytracer.h"

class Ray {
    public:
        Ray() : mint(0.f), maxt(INFINITY), depth(0) { }
        Ray(const Vec3 &origin, const Vec3 &direction,
            float start = 0.0f, float end = INFINITY, int d = 0)
            : o(origin), d(direction), mint(start), maxt(end), depth(d) { }

        Vec3 operator()(float t) const { return o + d * t; }

        Vec3 o;
        Vec3 d;
        mutable float mint;
        mutable float maxt;
        int depth;
};

#endif
