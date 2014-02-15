#include "triangle.h"

bool Triangle::Intersect(const Ray &ray, Intersection *isect) {
    /*
    if((!isect->obj || t < isect->t) && t > 0.0) {
        FillIntersection(isect, t, ray);
        return true;
    }
    */
    return false;
}

Vec3 Sphere::Normal(Vec3 p) const {

}

string Sphere::Description() const {
    string s = "Triangle";
    return s;
}
