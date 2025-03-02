#include "engine.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <fstream>

#include "../material/material.hpp"
#include "../lambertian/lambertian.hpp"
#include "../dielectric/dielectric.hpp"
#include "../metal/metal.hpp"

#include "../sphere/sphere.hpp"

#include <SFML/Graphics.hpp>

Engine::Engine(std::string config_path) {

    parseJson(config_path);

    save_img = config_data["b_img_gen_permission"];

    setupCam();
    setupWindow();
    setupScene();
}

void Engine::parseJson(std::string config_path) {
    std::ifstream config_file(config_path);
    config_data = Json::parse(config_file);
    config_file.close();
}

std::shared_ptr<Material> material_properties (Json material) {
    std::string type = material["type"];

    if (type == "metal")
        return std::make_shared<Metal>(
            Color(
                material["color"]["r"],
                material["color"]["g"],
                material["color"]["b"]
            ),
            material["fuzz"]
        );

    else if (type == "dielectric")
        return std::make_shared<Dielectric>(
            material["refractive_index"]
        );

    else if (type == "lambertian")
        return std::make_shared<Lambertian>(
            Color(
                material["color"]["r"],
                material["color"]["g"],
                material["color"]["b"]
            )
        );

    else {
        std::cout << "Invalid type detected, please check scene.json" << std::endl;
        return nullptr;
    }
};

void Engine::setupScene() {

    std::vector<std::shared_ptr<Hittable>> object_list;

    Json objs = config_data["objects"];

    for (int i = 0; i < objs.size(); i++) {

        Json obj = objs[i];

        Point3 position = Point3(
            obj["pos"]["x"],
            obj["pos"]["y"],
            obj["pos"]["z"]
        );

        float radius = obj["radius"];

        object_list.push_back(
            std::make_shared<Sphere>(
                position,
                radius,
                material_properties(obj["material"])
            )
        );
    }

    S_scene.setup(object_list);
}

void Engine::setupCam() {

    float        aspect_ratio = (float)config_data["f_aspect_ratio"]["width"] / config_data["f_aspect_ratio"]["height"];

    float        angle        = config_data["f_cam_defocus_angle"];
    float        focal_length = config_data["f_focal_length"];

    unsigned int width        = config_data["u_img_width"];
    unsigned int samples      = config_data["u_samples_per_pixel"];
    unsigned int bounces      = config_data["u_max_light_bounce"];
    unsigned int threads      = config_data["u_max_threads"];

    int          vfov         = config_data["i_vfov"];

    Point3 origin = Point3(
        config_data["P3_cam_origin"]["x"],
        config_data["P3_cam_origin"]["y"],
        config_data["P3_cam_origin"]["z"]
    );

    Point3 target = Point3(
        config_data["P3_target_capture_pos"]["x"],
        config_data["P3_target_capture_pos"]["y"],
        config_data["P3_target_capture_pos"]["z"]
    );

    Vec3 vertical = Vec3(
        config_data["V3_cam_y_unit"]["x"],
        config_data["V3_cam_y_unit"]["y"],
        config_data["V3_cam_y_unit"]["z"]
    );


    Cam_camera.set_aspect_ratio       (aspect_ratio);
    Cam_camera.set_img_width          (width);
    Cam_camera.set_samples_per_pixel  (samples);
    Cam_camera.set_max_light_bounce   (bounces);
    Cam_camera.set_threads_count      (threads);
    Cam_camera.set_vfov               (vfov);
    Cam_camera.set_origin             (origin);
    Cam_camera.set_capture_target_pos (target);
    Cam_camera.set_y_unit             (vertical);
    Cam_camera.set_defocus_angle      (angle);
    Cam_camera.set_focal_length       (focal_length);
}

void Engine::setupWindow() {

    std::string  title        = config_data["str_title"];
    unsigned int width        = config_data["u_win_width"];
    float        aspect_ratio = (float)config_data["f_aspect_ratio"]["width"] / config_data["f_aspect_ratio"]["height"];

    sf::Vector2u dimensions   = sf::Vector2u(
        width,
        (unsigned int) width / aspect_ratio
    );

    sf::Color    background   = sf::Color(
        config_data["clr_win_bg"]["r"],
        config_data["clr_win_bg"]["g"],
        config_data["clr_win_bg"]["b"]
    );

    WM_window.setup(title, dimensions, background);
}

void Engine::run() {
    std::cout << "Running Ray Tracing Version 0.0.1" << std::endl;

    Hittable_list& HL_ref_scene = S_scene.create_scene();

    std::cout << "Scene Generated Successfully" << std::endl;

    sf::Image* I_ref_image = Cam_camera.render(HL_ref_scene);

    std::cout << "Image Generated Successfully" << std::endl;

    if (save_img)
        I_ref_image->saveToFile("./imgs/rendered_img.png");

    std::cout << "Image Saved Successfully" << std::endl;

    WM_window.display(I_ref_image);
}
