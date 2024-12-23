#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "../camera/camera.hpp"

#include "../config.hpp"

class Engine {
    public:
        Engine(Configuration C_config);
        void run();

    private:
        Window_manager WM_window;
        Scene S_scene;
        Camera Cam_camera;
};

#endif
