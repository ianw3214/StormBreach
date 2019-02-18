#pragma once

#include "ECS/system.hpp"
#include "memory/pointers.hpp"

class Game;
class EnemySystem : public System {
public:
    EnemySystem(Reference<Game> ref);
    virtual void update(float delta);
private:
    unsigned int findTarget();
private:
    Reference<Game> game;
};