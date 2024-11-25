#ifndef HIT_RECORD_HPP
#define HIT_RECORD_HPP

#include "../vec3/vec3.hpp"
#include "../ray/ray.hpp"

#include <memory>

class Material;

class Hit_record {
    public:
        Point3 p;
        Vec3 normal;
        double t;
        bool front_face;

        std::shared_ptr<Material> mat;

        void set_face_normal(const Ray&, const Vec3&);

};

#endif
