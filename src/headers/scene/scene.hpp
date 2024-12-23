#ifndef SCENE_HPP
#define SCENE_HPP

#include "../hittable_list/hittable_list.hpp"
#include "../hittable/hittable.hpp"

#include <memory>
#include <vector>

class Scene {
    public:
        Scene(std::vector<std::shared_ptr<Hittable>>);
        Hittable_list& create_scene();
    private:
        Hittable_list HL_world;
        std::vector<std::shared_ptr<Hittable>> vec_Obj_objects;
};

#endif
