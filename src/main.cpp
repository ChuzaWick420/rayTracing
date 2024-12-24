#include "./headers/engine/engine.hpp"
#include "./headers/config.hpp"

int main () {

    Configuration C_configs;
    Engine E_engine(C_configs);
    E_engine.run();

    return 0;
}
