#include "plane.h"

bool Plane::Intersect(const Ray &ray, Intersection *isect) {
    float t = -ray.o.y / ray.d.y;

    if((!isect->obj || (t > 0.0 && t < isect->t)) && t > 0.0) {
        FillIntersection(isect, t, ray);
        return true;
    }

    return false;
}

Vec3 Plane::Normal(Vec3 p, Vec3 dir) const {
    Vec3 n = Vec3(0.0, 1.0, 0.0);
    if(n.Dot(dir) > 0.0) {
        n = -n;
    }
    return n;
}

string Plane::Description() const {
    string s = "Plane";
    return s;
}
