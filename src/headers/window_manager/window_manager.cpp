#include "./window_manager.hpp"

Window_manager::Window_manager(std::string title, sf::Vector2u dimensions) :
    u_width(dimensions.x),
    u_height(dimensions.y),
    R_window(sf::VideoMode({u_width, u_height}), title, sf::Style::Default)
{}
