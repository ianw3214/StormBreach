#pragma once

constexpr int MAX_ENTITIES = 100;

#include <SDL2/SDL.h>
#include <vector>

#include "memory/pointers.hpp"

#include "ECS/ECS.hpp"

struct DrawData {
    int z;
    int x;
    int y;
    int w;
    int h;
    int src_x;
    int src_y;
    int src_w;
    int src_h;
    std::string name;
    DrawData() {}
    DrawData(int z, int x, int y, int w, int h, int src_x, int src_y, int src_w, int src_h, const std::string& name) :
        z(z), x(x), y(y), w(w), h(h), src_x(src_x), src_y(src_y), src_w(src_w), src_h(src_h), name(name) {}
    bool operator<(const DrawData& other) {
        return z < other.z;
    }
};

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

    void drawTexture(DrawData& data);

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

    // Deffered rendering
    std::vector<DrawData> draw_objects;

    // ECS things
    std::vector<System*> systems;
    EntityManager entities;

    // Components
    ComponentManager<Position> positions;
    ComponentManager<Sprite> sprites;
    ComponentManager<Camera> cameras;
};