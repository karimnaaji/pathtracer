#include "triangle.h"

bool Triangle::Intersect(const Ray &ray, Intersection *isect) {
    Ray rt = ApplyTransform(ray);
    Vec3 e1 = p2 - p1;
    Vec3 e2 = p3 - p1;

    Vec3 s1 = rt.d.Cross(e2);
    float divisor = s1.Dot(e1);
    if(divisor == 0.0) 
        return false;

    float invDivisor = 1.0f / divisor;
    Vec3 d = rt.o - p1;
    float b1 = d.Dot(s1) * invDivisor;
    if(b1 < 0.0 || b1 > 1.0)
        return false;

    Vec3 s2 = d.Cross(e1);
    float b2 = ray.d.Dot(s2) * invDivisor;
    if(b2 < 0.0 || b1 + b2 > 1.0)
        return false;

    float t = e2.Dot(s2) * invDivisor;
    if(t < rt.mint || t > rt.maxt)
        return false;

    if((!isect->obj || t < isect->t) && t > 0.0) {
        FillIntersection(isect, t, ray);
        return true;
    }
    
    return false;
}

Vec3 Triangle::Normal(Vec3 p) const {
    return (p1 - p2).Cross(p1 - p3);
}

string Triangle::Description() const {
    string s = "Triangle";
    return s;
}
