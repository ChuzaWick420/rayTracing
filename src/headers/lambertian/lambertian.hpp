#ifndef LAMBERTIAN_HPP
#define LAMBERTIAN_HPP

#include "../material/material.hpp"
#include "../color3/color3.hpp"

class lambertian : public material {
  public:
    lambertian(const color& albedo) : albedo(albedo) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
        auto scatter_direction = rec.normal + random_unit_vector();

        if (scatter_direction.near_zero())
            scatter_direction = rec.normal;

        scattered = ray(rec.p, scatter_direction);

        attenuation = albedo;
        return true;
    }

  private:
    color albedo;
};

#endif 
