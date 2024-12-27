#include "./scene.hpp"
#include "../sphere/sphere.hpp"
#include "../material/material.hpp"

#include <iostream>

#include <memory>
#include <vector>

Scene::Scene() {}

Scene::Scene(std::vector<std::shared_ptr<Hittable>> objects) : 
    vec_Obj_objects(objects)
{}

Hittable_list& Scene::create_scene() {

    for (auto itr = vec_Obj_objects.begin(); itr != vec_Obj_objects.end(); itr++) {
        HL_world.add(*itr);
    }

    return HL_world;
}

void Scene::setup(std::vector<std::shared_ptr<Hittable>> objects) {
    vec_Obj_objects = objects;
}
