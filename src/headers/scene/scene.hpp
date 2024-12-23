#ifndef SCENE_HPP
#define SCENE_HPP

#include "../hittable_list/hittable_list.hpp"

#include "../config.hpp"
#include <vector>

class Scene {
    public:
        Scene(std::vector<Object>);
        Hittable_list* create_scene();
    private:
        Hittable_list HL_world;
        std::vector<Object> vec_Obj_objects;
};

#endif
