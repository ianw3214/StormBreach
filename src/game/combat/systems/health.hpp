#pragma once

#include "ECS/system.hpp"
#include "memory/pointers.hpp"

class Game;
class HealthSystem : public System {
public:
    HealthSystem(Reference<Game> ref);
    virtual void update(float delta);
private:
    Reference<Game> game;
};