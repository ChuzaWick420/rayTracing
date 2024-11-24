#include "./hittable_list.hpp"


Hittable_list::Hittable_list() {}


Hittable_list::Hittable_list(shared_ptr<Hittable> object) {
    add(object); 
}

void Hittable_list::clear() {
    objects.clear(); 
}

void Hittable_list::add(shared_ptr<Hittable> object) {
    objects.push_back(object);
}

