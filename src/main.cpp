#include "./headers/engine/engine.hpp"

int main () {

    Engine E_engine("./src/headers/config.json");
    E_engine.run();

    return 0;
}
