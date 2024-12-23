#include "engine.hpp"

Engine::Engine(Configuration C_config) :
    WM_window(C_config.title, sf::Vector2u(
        C_config.u_win_width,
        C_config.u_win_width / C_config.aspect_ratio
    )),
    S_scene(C_config.objects)
{}
