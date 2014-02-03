#include "plane.h"

bool Plane::Intersect(const Ray &ray, Intersection *isect) {
    float t = -ray.o.y / ray.d.y;

    if(!isect->obj || (t > 0.0 && t < isect->t)) {
        FillIntersection(isect, t, ray);
        return true;
    }

    return false;
}

Vec3 Plane::Normal(Vec3 p) const {
    return Vec3(0.0, 1.0, 0.0);
}

ostream& Plane::Description(ostream& o) const {
    o << "Plane";
    return o;
}
