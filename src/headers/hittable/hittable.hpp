#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "../interval/interval.hpp"
#include "../vec3/vec3.hpp"
#include "../ray/ray.hpp"

class Material;

class Hit_record {
    public:
        Point3 p;
        Vec3 normal;
        double t;
        bool front_face;

        shared_ptr<Material> mat;

        void set_face_normal(const Ray&, const Vec3&);

};

class Hittable {
    public:
        virtual ~Hittable() = default;

        virtual bool hit(const Ray&, Interval, Hit_record&) const = 0;
};

#endif
