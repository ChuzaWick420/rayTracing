#include "./hittable_list.hpp"


hittable_list::hittable_list() {}


hittable_list::hittable_list(shared_ptr<hittable> object) {
    add(object); 
}

void hittable_list::clear() {
    objects.clear(); 
}

void hittable_list::add(shared_ptr<hittable> object) {
    objects.push_back(object);
}

