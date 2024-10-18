#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "hittable.hpp"

class sphere : public hittable {
    public:
        sphere(const point3& center, double radius) : center(center), radius(std::fmax(0,radius)) {}


        bool hit(const ray&, interval, hit_record&) const override;

    private:
        point3 center;
        double radius;
};

#endif
