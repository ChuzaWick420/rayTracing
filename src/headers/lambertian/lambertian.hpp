#ifndef LAMBERTIAN_HPP
#define LAMBERTIAN_HPP

#include "../material/material.hpp"
#include "../color3/color3.hpp"

class Lambertian : public Material {
  public:
    Lambertian(const Color& albedo) : albedo(albedo) {}

    bool scatter(const Ray& r_in, const Hit_record& rec, Color& attenuation, Ray& scattered) const override {
        auto scatter_direction = rec.normal + random_unit_vector();

        if (scatter_direction.near_zero())
            scatter_direction = rec.normal;

        scattered = Ray(rec.p, scatter_direction);

        attenuation = albedo;
        return true;
    }

  private:
    Color albedo;
};

#endif 
