#include "bvh.h"

BVH::BVH(const vector<Object*>& objects) {
    vector<BVHNodeInfo> nodeInfos;  

    for(uint32_t i = 0; i < objects.size(); ++i) {
        BBox bbox = objects[i]->Bounds();
        nodeInfos.push_back(BVHNodeInfo(i, bbox));
    }

    root = RecursiveBuild(objects, nodeInfos, 0, objects.size());
}


BVHNode* BVH::RecursiveBuild(const vector<Object*>& objects, const vector<BVHNodeInfo>& nodeInfos, uint32_t start, uint32_t end) {
    BVHNode *node = new BVHNode();
    uint32_t nObjects = end - start;

    if(nObjects == 1) {
        BBox bbox = Union(nodeInfos[start].bounds, nodeInfos[end].bounds);
        node->InitLeaf(nObjects, bbox, objects[start], objects[end]);
    } else {
        uint32_t mid = (start + end) / 2;
        BVHNode* n1 = RecursiveBuild(objects, nodeInfos, start, mid);
        BVHNode* n2 = RecursiveBuild(objects, nodeInfos, mid, end);
        node->InitNode(n1, n2);
    }

    return node;
}

void BVH::Display(BVHNode *node, int depth) {
    if(node->children[0] != NULL) Display(node->children[0], depth + 1);
    if(node->children[1] != NULL) Display(node->children[1], depth + 1);

    cout << depth << endl;
    if(node->objects[0] != NULL) cout << *node->objects[0] << endl;
    if(node->objects[1] != NULL) cout << *node->objects[1] << endl;
}

BVH::~BVH() {
}
