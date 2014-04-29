#include "camera.h"

Camera::Camera() {
    lensRadius = 0.0f;
    focalDistance = 0.0f;
}

Camera::Camera(Vec3 &pos, Vec2 &resolution, float lensRad, float focal) 
    : cp(pos), lensRadius(lensRad), focalDistance(focal) {
    film = new PPMImage(resolution.x, resolution.y);
}

Camera::~Camera() {
    if(film != NULL) 
        delete film;
}

void Camera::LookAt(const Vec3 &p) {
    Vec3 up = Vec3::Up();
    cd = (p - cp).Normalize();
    cr = cd.Cross(up).Normalize();
    cu = cr.Cross(cd).Normalize();
}

float Camera::getLensRadius() const {
    return lensRadius;
}

float Camera::getFocalDistance() const {
    return focalDistance;
}

Vec2 Camera::SampleLens() const {
    Vec2 uv;
    uv.x = (2.0 * rand_0_1() - 1.0) * lensRadius;
    uv.y = (2.0 * rand_0_1() - 1.0) * lensRadius;
    return uv;
}

Ray Camera::PrimaryRay(const Vec2& sp) const {
    Vec2 p = -2.0f * sp + 1.0f; 
    Vec3 rd = (cr * p.x + cu * p.y + cd).Normalize();
    Ray r = Ray(cp, rd);
    return r;
}
