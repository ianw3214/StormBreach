#pragma once

#include "ECS/system.hpp"
#include "memory/pointers.hpp"

class Game;
class MouseClickSystem : public System {
public:
    MouseClickSystem(Reference<Game> ref);
    virtual void update(float delta);
private:
    void renderBuildButtons(int m_x, int m_y);
    void renderBlueprint(int m_x, int m_y);
private:
    Reference<Game> game;
};