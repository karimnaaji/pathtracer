#include "sphere.h"

bool Sphere::Intersect(const Ray &ray, Intersection *isect) {
    Ray rt = ApplyTransform(ray);
    Vec3 oc = rt.o - position;
    float b = 2.0 * oc.Dot(rt.d);
    float c = oc.Dot(oc) - 1.0;
    float delta = b*b - 4.0*c;

    if(delta < 0.0) 
        return false;

    float t = (-b - sqrt(delta)) * 0.5;

    if((!isect->obj || t < isect->t) && t > 0.0) {
        FillIntersection(isect, t, ray);
        return true;
    }
    
    return false;
}

Vec3 Sphere::Normal(Vec3 p) const {
    return (p - position).Normalize();
}

string Sphere::Description() const {
    string s = "Sphere";
    return s;
}
