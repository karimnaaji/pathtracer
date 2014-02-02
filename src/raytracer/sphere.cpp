#include "sphere.h"

bool Sphere::Intersect(const Ray &ray, Intersection *isect) {
    Vec3 oc = ray.o - position;
    float b = 2.0 * oc.Dot(ray.d);
    float c = oc.Dot(oc) - 1.0;
    float delta = b*b - 4.0*c;

    if(delta < 0.0) 
        return false;

    isect->t = (-b - sqrt(delta)) * 0.5;
    return true;
}
