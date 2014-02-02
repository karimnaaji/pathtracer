#include "camera.h"

void Camera::LookAt(const Vec3 &p) {
    Vec3 up = Vec3::Up();
    cd = (p - cp).Normalize();
    cr = cd.Cross(up).Normalize();
    cu = cr.Cross(cd).Normalize();
}
