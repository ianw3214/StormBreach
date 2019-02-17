#pragma once

constexpr int MAX_ENTITIES = 100;

#include <SDL2/SDL.h>
#include <vector>

#include "memory/pointers.hpp"

#include "ECS/ECS.hpp"

class Engine;
class State {
public:
    State();
    virtual ~State();

    void setEngineRef(Reference<Engine> ref);
    // Defer initialization because engine reference needs to be set first
    void base_init();
    // Callback for subclasses to customize initialization
    virtual void init();

    void onEvent(SDL_Event& e);
    void update(float delta);

    System * addSystem(System * system);
    unsigned int addEntity();

    EntityManager& getEntities();
    ComponentManager<Position>& getPositions();
    ComponentManager<Sprite>& getSprites();
    ComponentManager<Camera>& getCamera();

    Reference<Engine> getEngineRef();
protected:
    Reference<Engine> engine;

    // ECS things
    std::vector<System*> systems;
    EntityManager entities;

    // Components
    ComponentManager<Position> positions;
    ComponentManager<Sprite> sprites;
    ComponentManager<Camera> cameras;
};