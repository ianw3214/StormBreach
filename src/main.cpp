#include "engine.hpp"

#include "game/combat/game.hpp"

int main(int argc, char* argv[]) {

    EngineConfig config;
    config.window_width = 1280;
    config.window_height = 720;
    config.window_name = "TEST";
    Engine engine(config);

    engine.setState(new Game());

    engine.run();

    return 0;

}