#pragma once

constexpr int MAX_ENTITIES = 100;

#include <SDL2/SDL.h>
#include <vector>

#include "memory/pointers.hpp"
#include "util/vec.hpp"
#include "resource.hpp"

#include "ECS/ECS.hpp"

enum class DrawMethod {
    TEXTURE,
    LINE,
    SQUARE,
    SQUARE_OUTLINE,
    TEXT
};
struct DrawData {
    int z;
    // Shared drawing things
    int x;
    int y;
    // Drawing for rectangle-ish things
    int w;
    int h;
    // Texture drawing
    int src_x;
    int src_y;
    int src_w;
    int src_h;
    std::string name;       // <-- Share name for texture name and text content
    // Primitive drawing
    Colour colour;
    // Line drawing
    int x2;
    int y2;
    // Text drawing
    float scale;
    // Custom shader if desired
    ShaderRef shader;
    DrawMethod method;
    DrawData() {}
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

    void draw(DrawData& data);

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