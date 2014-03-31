#ifndef __BBOX_H__
#define __BBOX_H__

#include "config.h"
#include "ray.h"

enum Dimension { DIM_X, DIM_Y, DIM_Z };

class BBox {
    public:
        Vec3 min, max;
        BBox() {};
        BBox(const Vec3 &min, const Vec3 &max);
        bool Intersect(const Ray &ray, float *mint, float *maxt);
        Dimension Extent();

        friend BBox Union(const BBox &box1, const BBox &box2);
        friend BBox Union(const BBox &b, const Vec3 &p);
};

BBox Union(const BBox &box1, const BBox &box2);
BBox Union(const BBox &b, const Vec3 &p);

#endif
