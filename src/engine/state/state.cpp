#include "state.hpp"

#include "engine.hpp"

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
    // NOTE: this is all testing code
    // engine->getResources()->loadTexture("test", "res/test.png");
    // unsigned int id = addEntity();
    // positions.addComponent(id, {0, 0});
    // entities.setEntityComponent(id, COMP_POS);
    // sprites.addComponent(id, {150, 150, 0, 0, 0, 0, 0, 0, "test"});
    // entities.setEntityComponent(id, COMP_SPRITE);
}

void State::setEngineRef(Reference<Engine> ref) {
    engine = ref;
}

void State::onEvent(SDL_Event& e) {
    // Do nothing for now...
}

void State::update(float delta) {
    for (System * system : systems) {
        system->update(delta);
    }
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