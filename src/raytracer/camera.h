#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "ray.h"
#include "config.h"

class Camera {
    public:
        Camera() {}
        Camera(Vec3 &pos, Vec2 &resolution);
        ~Camera();
        void LookAt(const Vec3 &p);

        Vec3 GetRight() const { return cr; }
        Vec3 GetUp() const { return cu; }
        Vec3 GetDir() const { return cd; }
        Vec3 GetPos() const { return cp; }

        Ray PrimaryRay(const Vec2& sp) const;
        PPMImage* Film() const { return film; }

    private:
        Vec3 cp;
        Vec3 cd;
        Vec3 cr;
        Vec3 cu;
        PPMImage *film;
};

#endif
