#include "vec3.h"

Vec3::Vec3() {
    x = 0;
    y = 0;
    z = 0;
}

Vec3::Vec3(float x_,float y_,float z_) {
    x = x_;
    y = y_;
    z = z_;
}

Vec3::Vec3(float val) {
    x = val;
    y = val;
    z = val;
}

Vec3::Vec3(const Vec3& v) {
    x = v.x;
    y = v.y;
    z = v.z;
}

Vec3::Vec3(const Vec3& from,const Vec3& to) {
    x = to.x - from.x;
    y = to.y - from.y;
    z = to.z - from.z;
}

Vec3& Vec3::operator=(const Vec3& v) {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

Vec3& Vec3::operator+=(const Vec3& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vec3 Vec3::operator+(const Vec3& v) const {
    Vec3 t = *this;
    t += v;
    return t;
}

Vec3& Vec3::operator-=(const Vec3& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Vec3 Vec3::operator-(const Vec3& v) const {
    Vec3 t = *this;
    t -= v;
    return t;
}

Vec3 Vec3::operator-() const {
    Vec3 t = *this * -1.0f;
    return t;
}

Vec3& Vec3::operator*=(const float a) {
    x *= a;
    y *= a;
    z *= a;
    return *this;
}

Vec3 Vec3::operator*(const float a) const {
    Vec3 t = *this;
    t *= a;
    return t;
}

Vec3 operator*(const float a ,const Vec3& v) {
    return Vec3(v.x*a,v.y*a,v.z*a);
}

Vec3 Vec3::operator*(const Vec3& v) const {
    return Vec3(x*v.x, y*v.y, z*v.z);
}

Vec3& Vec3::operator/=(const float a) {
    x /= a;
    y /= a;
    z /= a;
    return *this;
}

Vec3 Vec3::operator/(const float a) const {
    Vec3 t = *this;
    t /= a;
    return t;
}

Vec3 Vec3::Cross(const Vec3& v) const {
    Vec3 t;
    t.x = y*v.z - z*v.y;
    t.y = z*v.x - x*v.z;
    t.z = x*v.y - y*v.x;
    return t;
}

Vec3 Vec3::Abs(Vec3 v) {
    v.x = fabs(v.x);
    v.y = fabs(v.y);
    v.z = fabs(v.z);
    return v;
}

Vec3 Vec3::VClamp(Vec3 v, float low, float high) {
    v.x = Clamp(v.x, low, high);
    v.y = Clamp(v.y, low, high);
    v.z = Clamp(v.z, low, high);
    return v;
}

float Vec3::Dot(const Vec3& v) const {
    return x*v.x + y*v.y + z*v.z;
}

Vec3 Vec3::Up() {
    return Vec3(0.0, 1.0, 0.0);
}

float Vec3::Length() const {
    return sqrt(x*x + y*y + z*z);
}

Vec3& Vec3::Normalize() {
    (*this) /= Length();
    return (*this);
}

Vec3 Vec3::Zero() {
    return Vec3(0, 0, 0);
}
