#ifndef __VEC3_H__
#define __VEC3_H__

#include <cmath>

class Vec3 {
    public:
        union {
            struct { float x, y, z; };
            struct { float r, g, b; };
            float v[3];
        };
        
        Vec3();
        Vec3(float x,float y,float z);
        Vec3(float val);
        Vec3(const Vec3& v);
        Vec3(const Vec3& from,const Vec3& to);
        
        Vec3& operator=(const Vec3& v);
        Vec3& operator+=(const Vec3& v);
        Vec3 operator+(const Vec3& v) const;        
        Vec3& operator-=(const Vec3& v);
        Vec3 operator-(const Vec3& v) const;        
        Vec3& operator*=(const float a);
        Vec3 operator*(const float a)const;
        Vec3 operator*(const Vec3& v) const;
        Vec3& operator/=(const float a);
        Vec3 operator/(const float a)const;
        friend Vec3 operator*(const float a, const Vec3& v);

        static Vec3 Zero();
        static Vec3 Abs(Vec3 v);
        static Vec3 Up();
        Vec3 Cross(const Vec3& v) const;
        float Length() const;
        float Dot(const Vec3& v) const;
        Vec3& Normalize();
};

#endif 
