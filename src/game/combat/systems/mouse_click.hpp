#pragma once

#include "ECS/system.hpp"
#include "memory/pointers.hpp"

class Game;
class MouseClickSystem : public System {
public:
    MouseClickSystem(Reference<Game> ref);
    virtual void update(float delta);
private:
    Reference<Game> game;
};