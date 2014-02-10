#include "camera.h"

void Camera::LookAt(const Vec3 &p) {
    Vec3 up = Vec3::Up();
    cd = (p - cp).Normalize();
    cr = cd.Cross(up).Normalize();
    cu = cr.Cross(cd).Normalize();
}

Ray Camera::PrimaryRay(const Vec2& sp) const {
    Vec2 p = -2.0f * sp + 1.0f; 
    Vec3 rd = (cr * p.x + cu * p.y + cd).Normalize();
    Ray r = Ray(cp, rd);
    return r;
}
