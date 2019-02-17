#pragma once

#include "ECS/system.hpp"
#include "memory/pointers.hpp"

class Game;
class RainSystem : public System {
public:
    RainSystem(Reference<Game> ref);
    virtual void update(float delta);
private:
    Reference<Game> game;
};