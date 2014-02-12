#include "plane.h"

bool Plane::Intersect(const Ray &ray, Intersection *isect) {
    Ray rt = ApplyTransform(ray);
    float t = -rt.o.y / rt.d.y;

    if((!isect->obj || (t > 0.0 && t < isect->t)) && t > 0.0) {
        FillIntersection(isect, t, ray);
        return true;
    }

    return false;
}

Vec3 Plane::Normal(Vec3 p) const {
    return Vec3(0.0, 1.0, 0.0);
}

string Plane::Description() const {
    string s = "Plane";
    return s;
}
