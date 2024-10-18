#include "./color3.hpp"
#include "../interval/interval.hpp"

#include "SFML/Graphics.hpp"

void write_color(sf::Color& pixel, const color& pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Translate the [0,1] component values to the byte range [0,255].

    static const interval intensity(0.000, 0.999);

    pixel.r = int(256 * intensity.clamp(r));
    pixel.g = int(256 * intensity.clamp(g));
    pixel.b = int(256 * intensity.clamp(b));

}
