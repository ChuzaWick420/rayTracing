#ifndef HITTABLE_LIST_HPP
#define HITTABLE_LIST_HPP

#include "../hittable/hittable.hpp"
#include "../ray/ray.hpp"
#include "../interval/interval.hpp"

#include "../main_header.hpp"

#include <vector>

class hittable_list : public hittable {
    public:
        std::vector<shared_ptr<hittable>> objects;

        hittable_list();
        hittable_list(shared_ptr<hittable>);

        void clear();

        void add(shared_ptr<hittable>);

        bool hit(const ray& r, interval ray_t, hit_record& rec) const override{

            hit_record temp_rec;
            bool hit_anything = false;
            auto closest_so_far = ray_t.max;

            for (const auto& object : objects) {
                if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec)) {
                    hit_anything = true;
                    closest_so_far = temp_rec.t;
                    rec = temp_rec;
                }
            }

            return hit_anything;
        }
};

#endif
