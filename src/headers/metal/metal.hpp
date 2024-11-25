#ifndef METAL_HPP
#define METAL_HPP

#include "../material/material.hpp"
#include "../color/color.hpp"
#include "../hit_record/hit_record.hpp"
#include "../ray/ray.hpp"
#include "../vec3/vec3.hpp"

#include "../utils.hpp"

class Metal : public Material {
    public:
        Metal(const Color& albedo, double fuzz) :
            albedo(albedo),
            fuzz(fuzz < 1 ? fuzz : 1)
        {}

        bool scatter(const Ray& r_in, const Hit_record& rec, Color& attenuation, Ray& scattered) const override {
            Vec3 reflected = reflect(r_in.direction(), rec.normal);
            reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
            scattered = Ray(rec.p, reflected);
            attenuation = albedo;
            return (dot(scattered.direction(), rec.normal) > 0);
        }

  private:
        Color albedo;
        double fuzz;
};

#endif
