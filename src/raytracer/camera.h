#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "raytracer.h"

class Camera {
    public:
        Camera(Vec3 &pos) : cp(pos) { }
        void LookAt(const Vec3 &p);

        Vec3 GetRight() const { return cr; }
        Vec3 GetUp() const { return cu; }
        Vec3 GetDir() const { return cd; }
        Vec3 GetPos() const { return cp; }

    private:
        Vec3 cp;
        Vec3 cd;
        Vec3 cr;
        Vec3 cu;
};

#endif
