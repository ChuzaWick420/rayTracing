#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "../hittable/hittable.hpp"
#include "../color3/color3.hpp"

class Material {
  public:
    virtual ~Material() = default;

    virtual bool scatter(
        const Ray& r_in, const Hit_record& rec, Color& attenuation, Ray& scattered
    ) const {
        return false;
    }
};

#endif
