#include "./headers/engine/engine.hpp"
#include "./headers/config.hpp"

int main () {

    Configuration configs;
    Engine engine(configs);
    engine.run();

    return 0;
}
