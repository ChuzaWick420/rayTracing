#ifndef HITTABLE_LIST_HPP
#define HITTABLE_LIST_HPP

#include "../hittable/hittable.hpp"
#include "../ray/ray.hpp"
#include "../interval/interval.hpp"

#include "../main_header.hpp"

class Hittable_list : public Hittable {
    public:
        std::vector<shared_ptr<Hittable>> objects;

        Hittable_list();
        Hittable_list(shared_ptr<Hittable>);

        void clear();

        void add(shared_ptr<Hittable>);

        bool hit(const Ray& r, Interval ray_t, Hit_record& rec) const override{

            Hit_record temp_rec;
            bool hit_anything = false;
            auto closest_so_far = ray_t.max;

            for (const auto& object : objects) {
                if (object->hit(r, Interval(ray_t.min, closest_so_far), temp_rec)) {
                    hit_anything = true;
                    closest_so_far = temp_rec.t;
                    rec = temp_rec;
                }
            }

            return hit_anything;
        }
};

#endif
