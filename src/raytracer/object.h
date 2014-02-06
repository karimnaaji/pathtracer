#ifndef __PRIMITIVE_H__
#define __PRIMITIVE_H__

#include "ray.h"
#include "intersection.h"
#include "material.h"
#include "raytracer.h"
#include "matrix4.h"

class Object {
    public:
        Object(Vec3 pos, Vec3 col, Vec3 emis) :
            position(pos), color(col), emission(emis) { }
        virtual bool Intersect(const Ray &ray, Intersection *isect) = 0;
        virtual ~Object() { }
        virtual ostream& Description(ostream& o) const = 0;
        Vec3 virtual Normal(Vec3 p) const = 0;

        Ray ApplyTransform(const Ray &ray) const {
            Ray rt(ray);
            rt.o = transform * ray.o;
            return rt;
        }

        void FillIntersection(Intersection* isect, float t, const Ray& ray) {
            isect->t = t;
            isect->obj = this;
            isect->p = ray(t);
            isect->n = Normal(isect->p);
        }

        Vec3 position;
        Vec3 color;
        Vec3 emission;
        MaterialType material;
        Matrix4 transform;

        Matrix4 GetTransform() const {
            Matrix4 T = Matrix4::CreateTranslation(-position);
            return T;
        }

		inline friend ostream& operator<<(ostream& o, const Object& obj) {
            o << obj.Description(o) << endl;
            o << "Position: " << obj.position << endl;
            o << "Color: " << obj.color << endl;
            o << "Material: ";
            switch(obj.material) {
                case E_DIFFUSE:  o << "E_DIFFUSE"  << endl; break;
                case E_REFRACT:  o << "E_REFRACT"  << endl; break;
                case E_SPECULAR: o << "E_SPECULAR" << endl; break;
            }
            return o;
        }
};

#endif
