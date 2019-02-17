#pragma once

#include "ECS/system.hpp"
#include "memory/pointers.hpp"

class Game;
class LightSystem : public System {
public:
    LightSystem(Reference<Game> ref);
    virtual void update(float delta);
private:
    Reference<Game> game;
};