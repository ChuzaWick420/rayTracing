#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "../camera/camera.hpp"
#include "../window_manager/window_manager.hpp"
#include "../scene/scene.hpp"

#include "../config.hpp"

class Engine {
    public:
        Engine(Configuration);
        void run();

    private:
        Window_manager WM_window;
        Scene S_scene;
        Camera Cam_camera;
        bool save_img = false;
};

#endif
