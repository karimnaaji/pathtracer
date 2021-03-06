#ifndef __INTERSECTION_H__
#define __INTERSECTION_H__

#include "config.h"

class Object;

class Intersection {
    public:
        Intersection() : t(0.0), obj(NULL) {}

		inline friend ostream& operator<<(ostream& o, const Intersection& isect) {
            o << "Intersection at " << isect.spos << ", t: " << isect.t << endl;
            o << "  n: " << isect.n << endl;
            o << "  p: " << isect.p;
            return o;
        }

        float t;
        Object *obj;
        Vec2 spos;
        Vec3 n;
        Vec3 p;
};

#endif
