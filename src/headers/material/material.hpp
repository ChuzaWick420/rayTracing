#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "../hittable/hittable.hpp"
#include "../color3/color3.hpp"

class material {
  public:
    virtual ~material() = default;

    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
    ) const {
        return false;
    }
};

#endif
