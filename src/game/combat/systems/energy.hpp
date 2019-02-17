#pragma once

#include "ECS/system.hpp"
#include "memory/pointers.hpp"

class Game;
class EnergySystem : public System {
public:
    EnergySystem(Reference<Game> ref);
    virtual void update(float delta);
private:
    Reference<Game> game;
};