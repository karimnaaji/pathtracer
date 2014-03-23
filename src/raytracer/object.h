#ifndef __PRIMITIVE_H__
#define __PRIMITIVE_H__

#include "ray.h"
#include "intersection.h"
#include "material.h"
#include "color.h"
#include "config.h"
#include "bbox.h"

class Object {
    public:
        Object(Vec3 pos, Color col, Color emis) :
            position(pos), color(col), emission(emis) {}
        virtual bool Intersect(const Ray &ray, Intersection *isect) = 0;
        virtual ~Object() {}
        virtual string Description() const = 0;
        Vec3 virtual Normal(Vec3 p, Vec3 dir) const = 0;
        BBox virtual Bounds() const = 0;

        bool Emit() const { 
            return emission.r > 0 || emission.g > 0 || emission.b > 0;
        }

        void FillIntersection(Intersection* isect, float t, const Ray& ray) {
            isect->t = t;
            isect->obj = this;
            isect->p = ray(t);
            isect->n = Normal(isect->p, ray.d);
        }

        Vec3 position;
        Color color;
        Color emission;
        MaterialType material;

		inline friend ostream& operator<<(ostream& o, const Object& obj) {
            o << obj.Description() << endl;
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

    private:
        Matrix4 transform;
};

#endif
