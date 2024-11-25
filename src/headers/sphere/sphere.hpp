#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "../hittable/hittable.hpp"
#include "../ray/ray.hpp"
#include "../material/material.hpp"
#include "../interval/interval.hpp"
#include "../hit_record/hit_record.hpp"
#include "../vec3/vec3.hpp"

#include "../utils.hpp"

#include <memory>

class Sphere : public Hittable {
    public:
        Sphere(const Point3& center, double radius, std::shared_ptr<Material> mat) : 
            center(center), 
            radius(std::fmax(0,radius)),
            mat(mat)
        {}


    bool hit(const Ray& r, Interval ray_t, Hit_record& rec) const override {
        Vec3 oc = center - r.origin();
        auto a = r.direction().length_squared();
        auto h = dot(r.direction(), oc);
        auto c = oc.length_squared() - radius*radius;

        auto discriminant = h*h - a*c;
        if (discriminant < 0)
            return false;

        auto sqrtd = std::sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (h - sqrtd) / a;
        if (!ray_t.surrounds(root)){
            root = (h + sqrtd) / a;

            if (!ray_t.surrounds(root))
                return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        rec.normal = (rec.p - center) / radius;

        Vec3 outward_normal = rec.normal;
        rec.set_face_normal(r, outward_normal);
        rec.mat = mat;

        return true;
}

    private:
        Point3 center;
        double radius;

        std::shared_ptr<Material> mat;
};

#endif
