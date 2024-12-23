#include "./scene.hpp"
#include "../sphere/sphere.hpp"
#include "../material/material.hpp"
#include "../config/predefined_materials.hpp"

#include <memory>
#include <vector>

Scene::Scene(std::vector<Object> objects) : 
    vec_Obj_objects(objects)
{}

Hittable_list* Scene::create_scene() {

    for (std::vector<Object>::iterator itr = vec_Obj_objects.begin(); itr != vec_Obj_objects.end(); itr++) {

        std::shared_ptr<Material> Mat_sptr_material;

        switch (itr->u_material_id) {
            case Material_id_map::LAMBERTIAN:
                Mat_sptr_material = Predefined_Materials::Lam_sptr_Lam_material;
                break;
            case Material_id_map::DIELECTRIC:
                Mat_sptr_material = Predefined_Materials::Di_sptr_Di_material;
                break;

            case Material_id_map::METAL:
                Mat_sptr_material = Predefined_Materials::Met_sptr_Met_material;
                break;
        }

        auto obj = std::make_shared<Sphere>(itr->p3_pos, itr->f_radius, Mat_sptr_material);
        HL_world.add(obj);
    }

    return &HL_world;
}
