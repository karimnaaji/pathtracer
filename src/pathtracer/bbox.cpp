#include "bbox.h"

BBox::BBox(const Vec3 &min, const Vec3 &max) {
    this->min = Vec3(Min(min.x, max.x), Min(min.y, max.y), Min(min.z, max.z));
    this->max = Vec3(Max(min.x, max.x), Max(min.y, max.y), Max(min.z, max.z));
}

bool BBox::Intersect(const Ray &ray, float *mint, float *maxt) {
    float t0 = ray.mint;
    float t1 = ray.maxt;
    for(int i = 0; i < 3; ++i) {
        float invRayDir = 1.0f / ray.d[i];
        float tNear = (min[i] - ray.o[i]) * invRayDir;
        float tFar  = (max[i] - ray.o[i]) * invRayDir;
        if(tNear > tFar) { 
            float tmp = tNear;
            tNear = tFar;
            tFar = tmp;
        }
        t0 = tNear > t0 ? tNear : t0;
        t1 = tFar  < t1 ? tFar  : t1;
        if(t0 > t1) return false;
    }
    if(mint) *mint = t0;
    if(maxt) *maxt = t1;
    return true;
}

Dimension BBox::Extent() {
    Vec3 diagonal = min - max;
    if(diagonal.x > diagonal.y && diagonal.x > diagonal.z)
        return DIM_X;
    else if(diagonal.y > diagonal.z)
        return DIM_Y;
    else 
        return DIM_Z;
}

BBox Union(const BBox &box1, const BBox &box2) {
    BBox box;
    box.min.x = Min(box1.min.x, box2.min.x);
    box.min.y = Min(box1.min.y, box2.min.y);
    box.min.z = Min(box1.min.z, box2.min.z);
    box.max.x = Max(box1.max.x, box2.max.x);
    box.max.y = Max(box1.max.y, box2.max.y);
    box.max.z = Max(box1.max.z, box2.max.z);
    return box;
}

BBox Union(const BBox &b, const Vec3 &p) {
    BBox box;
    box.min.x = Min(b.min.x, p.x);
    box.min.y = Min(b.min.y, p.y);
    box.min.z = Min(b.min.z, p.z);
    box.max.x = Max(b.max.x, p.x);
    box.max.y = Max(b.max.y, p.y);
    box.max.z = Max(b.max.z, p.z);
    return box;
}
    
