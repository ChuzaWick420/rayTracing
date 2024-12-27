#ifndef WINDOW_MANAGER_HPP
#define WINDOW_MANAGER_HPP

#include <string>

#include <SFML/Graphics.hpp>

class Window_manager {
    public:
        Window_manager();
        Window_manager(std::string, sf::Vector2u, sf::Color);
        void setup(std::string, sf::Vector2u, sf::Color);
        void display(const sf::Image* const);

    private:
        unsigned int u_width;
        unsigned int u_height;
        std::string str_title;
        sf::Color clr_bg_color;
        sf::RenderWindow R_window;
};

#endif
