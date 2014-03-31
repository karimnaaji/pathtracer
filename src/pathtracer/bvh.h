#ifndef __BVH_H__
#define __BVH_H__

#include "bbox.h"
#include "object.h"
#include "config.h"

struct BVHNodeInfo {
    BVHNodeInfo(uint32_t objn, const BBox &b) : objectNumber(objn), bounds(b) {
        centroid = 0.5f * b.min + 0.5f * b.max;
    }
    uint32_t objectNumber;
    BBox bounds;
    Vec3 centroid;
};

struct BVHNode {
    BVHNode() {
        children[0] = children[1] = NULL;
        objects[0] = objects[1] = NULL;
    }

    void InitLeaf(uint32_t n, const BBox& b, Object *o1, Object *o2) {
        nObjects = n;
        bounds = b;
        objects[0] = o1;
        objects[1] = o2;
    }

    void InitNode(BVHNode* n1, BVHNode* n2) {
        children[0] = n1;
        children[1] = n2;
        bounds = Union(n1->bounds, n2->bounds);
        nObjects = 0;
    }

    BBox bounds;
    BVHNode *children[2];
    Object *objects[2];
    uint32_t nObjects;
};

class BVH {
    public:
        BVH(const vector<Object*>& objects);
        ~BVH();
        BVHNode *root;
        void Display(BVHNode *node, int depth = 0);
    
    private:
        BVHNode* RecursiveBuild(const vector<Object*>& objects, const vector<BVHNodeInfo>& nodeInfos, uint32_t start, uint32_t end);
};

#endif
