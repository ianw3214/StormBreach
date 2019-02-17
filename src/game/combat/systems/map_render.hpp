#pragma once

#include "ECS/system.hpp"
#include "memory/pointers.hpp"

#include <vector>
struct PaletteData {
    std::string name;
    std::string path;
    PaletteData(const std::string& name, const std::string& path) : name(name), path(path) {}
};

class Game;
class MapRenderSystem : public System {
public:
    MapRenderSystem(Reference<Game> ref);
    virtual void update(float delta);
private:
    Reference<Game> game;

    // Information about tile sprites
    std::vector<PaletteData> palette;
};