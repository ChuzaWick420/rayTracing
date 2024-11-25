#include "./hittable_list.hpp"
#include "../hittable/hittable.hpp"

#include <memory>

Hittable_list::Hittable_list() {}


Hittable_list::Hittable_list(std::shared_ptr<Hittable> object) {
    add(object); 
}

void Hittable_list::clear() {
    objects.clear(); 
}

void Hittable_list::add(std::shared_ptr<Hittable> object) {
    objects.push_back(object);
}

