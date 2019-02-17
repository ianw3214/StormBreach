#include "state.hpp"

#include "engine.hpp"
#include "resource.hpp"
#include "renderer/renderer.hpp"

State::State() {
    // Do nothing because engine is not set yet
}

State::~State() {
    // Do nothing for now...
}

void State::base_init() {
    addSystem(new SpriteRenderSystem(this));
    addSystem(new CameraUpdateSystem(this));
    // Call the customized callback
    init();
}

void State::init() {
    // Do nothing in base class
}

void State::drawTexture(DrawData& data) {
    draw_objects.push_back(data);
}

void State::setEngineRef(Reference<Engine> ref) {
    engine = ref;
}

void State::onEvent(SDL_Event& e) {
    // Do nothing for now...
}

#include <iostream>
void State::update(float delta) {
    for (System * system : systems) {
        system->update(delta);
    }
    // TODO: (Ian) Only render the scene after a certain delta time has passed
    // Render the scene
    std::sort(draw_objects.begin(), draw_objects.end());
    for (const DrawData& obj : draw_objects) {
        if (obj.method == DrawMethod::TEXTURE) {
            if (engine->getResources()->getTexture(obj.name)) {
                engine->getRenderer()->drawTexture({obj.x, obj.y}, obj.w, obj.h, {obj.src_x, obj.src_y}, obj.src_w, obj.src_h, obj.name);
            } else {
                engine->getRenderer()->drawRect({obj.x, obj.y}, obj.w, obj.h, {1.f, 0.f, 1.f});
            }
        }
        if (obj.method == DrawMethod::SQUARE) {
            engine->getRenderer()->drawRect({obj.x, obj.y}, obj.w, obj.h, obj.colour);
        }
        if (obj.method == DrawMethod::SQUARE_OUTLINE) {
            engine->getRenderer()->drawRectOutline({obj.x, obj.y}, obj.w, obj.h, obj.colour);
        }
    }
    draw_objects.clear();
}

System * State::addSystem(System * system) {
    systems.push_back(system);
    return system;
}

unsigned int State::addEntity() {
    return entities.addEntity();
}

EntityManager& State::getEntities() {
    return entities;
}

ComponentManager<Position>& State::getPositions() {
    return positions;
}

ComponentManager<Sprite>& State::getSprites() {
    return sprites;
}
ComponentManager<Camera>& State::getCamera() {
    return cameras;
}

Reference<Engine> State::getEngineRef() {
    return engine;
}