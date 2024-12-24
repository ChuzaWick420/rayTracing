#include "./window_manager.hpp"

#include <iostream>

Window_manager::Window_manager(std::string title, sf::Vector2u dimensions, sf::Color background) :
    u_width(dimensions.x),
    u_height(dimensions.y),
    R_window(sf::VideoMode({u_width, u_height}), title, sf::Style::Default),
    clr_bg_color(background)
{}

void Window_manager::display(const sf::Image* const img) {

    sf::Texture T_img;
    T_img.loadFromImage(*img);

    sf::Sprite S_img(T_img);

    float scalar = float(u_width) / img->getSize().x;
    S_img.scale(sf::Vector2f(scalar, scalar));

    // debug
    std::cout << "Img: " << img->getSize().x << "x" << img->getSize().y << std::endl;
    std::cout << "Window: " << u_width << "x" << u_height << std::endl;

    while(R_window.isOpen()) {

        sf::Event event;
        while (R_window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                R_window.close();
        }

        R_window.clear(clr_bg_color);
        R_window.draw(S_img);
        R_window.display();
    }
}
