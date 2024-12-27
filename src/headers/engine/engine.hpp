#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "../camera/camera.hpp"
#include "../window_manager/window_manager.hpp"
#include "../scene/scene.hpp"

#include <string>

#include <nlohmann/json.hpp>

using Json = nlohmann::json;

class Engine {
    public:
        Engine(std::string);
        void run();

    private:
        Window_manager WM_window;
        Scene S_scene;
        Camera Cam_camera;

        bool save_img = false;

        Json config_data;

        void parseJson(std::string);

        void setupScene();
        void setupWindow();
        void setupCam();
};

#endif
