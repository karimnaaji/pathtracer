#include "sphere.h"

bool Sphere::Intersect(const Ray &ray, Intersection *isect) {
    Vec3 oc = ray.o - position;
    float b = 2.0 * oc.Dot(ray.d);
    float c = oc.Dot(oc) - 1.0;
    float delta = b*b - 4.0*c;

    if(delta < 0.0) 
        return false;

    float t = (-b - sqrt(delta)) * 0.5;

    if(!isect->obj || t < isect->t) {
        FillIntersection(isect, t, ray);
        return true;
    }
    
    return false;
}

Vec3 Sphere::Normal(Vec3 p) const {
    return (p - position).Normalize();
}

ostream& Sphere::Description(ostream& o) const {
    o << "Sphere";
    return o;
}
