#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "../interval/interval.hpp"
#include "../vec3/vec3.hpp"
#include "../ray/ray.hpp"

class material;

class hit_record {
    public:
        point3 p;
        vec3 normal;
        double t;
        bool front_face;

        shared_ptr<material> mat;

        void set_face_normal(const ray&, const vec3&);

};

class hittable {
    public:
        virtual ~hittable() = default;

        virtual bool hit(const ray&, interval, hit_record&) const = 0;
};

#endif
