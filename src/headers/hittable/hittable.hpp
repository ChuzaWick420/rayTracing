#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "../ray/ray.hpp"
#include "../interval/interval.hpp"
#include "../hit_record/hit_record.hpp"

class Hittable {
    public:
        virtual ~Hittable() = default;

        virtual bool hit(const Ray&, Interval, Hit_record&) const = 0;
};

#endif
