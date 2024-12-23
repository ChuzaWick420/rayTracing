#include "engine.hpp"

#include <iostream>

#include <SFML/Graphics.hpp>

Engine::Engine(Configuration C_config) :
    WM_window(
        C_config.title, {
            C_config.u_win_width,
            (unsigned int)(C_config.u_win_width / C_config.f_aspect_ratio)
        },
        C_config.clr_win_bg
    ),
    S_scene(C_config.objects),
    save_img(C_config.b_img_gen_permission)
{

    Cam_camera.aspect_ratio      = C_config.f_aspect_ratio;
    Cam_camera.img_width         = C_config.u_img_width;
    Cam_camera.samples_per_pixel = C_config.u_samples_per_pixel;
    Cam_camera.max_depth         = C_config.u_max_depth;
    Cam_camera.threads           = C_config.u_max_threads;
    Cam_camera.vfov              = C_config.i_vfov;
    Cam_camera.lookfrom          = C_config.p3_cam_origin;
    Cam_camera.lookat            = C_config.p3_target_capture_pos;
    Cam_camera.vup               = C_config.v3_cam_height;
    Cam_camera.defocus_angle     = C_config.f_cam_defocus_angle;
    Cam_camera.focus_dist        = C_config.f_local_length;

}

void Engine::run() {
    std::cout << "Running Ray Tracing Version 0.0.1" << std::endl;

    Hittable_list& HL_ref_scene = S_scene.create_scene();

    std::cout << "Scene Generated Successfully" << std::endl;

    sf::Image* I_ref_image = Cam_camera.render(HL_ref_scene);

    std::cout << "Image Generated Successfully" << std::endl;

    if (save_img)
        I_ref_image->saveToFile("./rendered_img.png");

    std::cout << "Image Saved Successfully" << std::endl;

    WM_window.display(I_ref_image);
}
