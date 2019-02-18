#include "game.hpp"

#include "engine.hpp"
#include "resource.hpp"
#include "systems/systems.hpp"

Game::Game() :
    show_build_menu(false),
    menu_x(0), menu_y(0),
    building(false),
    build_plant_button(0, 0, 180, 70),
    build_factory_button(0, 0, 180, 70)
{

}

Game::~Game() {

}

void Game::init() {
    engine->getResources()->loadTexture("plant", "res/units/power_plant.png");
    engine->getResources()->loadTexture("factory", "res/units/factory.png");

    addSystem(new MapRenderSystem(this));
    addSystem(new MouseClickSystem(this));
    addSystem(new EnergySystem(this));
    addSystem(new RainSystem(this));
    addSystem(new LightSystem(this));

    {   // Rain particles
        unsigned int id = addEntity();
        rain.addComponent(id, {100, std::vector<RainParticle>(100, RainParticle())});
        entities.setEntityComponent(id, COMP_RAIN);
    }
    {   // The tilemap entity
        unsigned int id = addEntity();
        TileMap tiles;
        tiles.width = 10;
        tiles.height = 10;
        tiles.tile_size = 128;
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                tiles.map.push_back(0);
            }
        }
        tilemap.addComponent(id, tiles);
        entities.setEntityComponent(id, COMP_TILEMAP);
        positions.addComponent(id, {0, 0, true});
        entities.setEntityComponent(id, COMP_POS);
    }
    {   // Camera entity
        unsigned int id = addEntity();
        positions.addComponent(id, {0, 0});
        entities.setEntityComponent(id, COMP_POS);
        cameras.addComponent(id, {CAM_FREE, 700.f, 150});
        entities.setEntityComponent(id, COMP_CAMERA);
    }
    {   // Starting power plant
        addPlant(200, 200);
    }
    {   // Starting factory
        addFactory(300, 300);
    }

}

void Game::addPlant(int x, int y) {
    unsigned int id = addEntity();
    positions.addComponent(id, Position(x, y, true, 1));
    entities.setEntityComponent(id, COMP_POS);
    sprites.addComponent(id, Sprite(100, 100, 0, 0, "plant"));
    entities.setEntityComponent(id, COMP_SPRITE);
    clickables.addComponent(id, Clickable{0, 0, 100, 100});
    entities.setEntityComponent(id, COMP_CLICK);
    selectables.addComponent(id, {});
    entities.setEntityComponent(id, COMP_SELECT);
    generateEnergy.addComponent(id, GenerateEnergy{3});
    entities.setEntityComponent(id, COMP_GEN_E);
    storeEnergy.addComponent(id, StoreEnergy{0, 100, 0, 0});
    entities.setEntityComponent(id, COMP_STORE_E);
    light.addComponent(id, {150, 50, 50});
    entities.setEntityComponent(id, COMP_LIGHT);
}

void Game::addFactory(int x, int y) {
    unsigned int id = addEntity();
    positions.addComponent(id, Position(x, y, true, 1));
    entities.setEntityComponent(id, COMP_POS);
    sprites.addComponent(id, Sprite(100, 100, 0, 0, "factory"));
    entities.setEntityComponent(id, COMP_SPRITE);
    clickables.addComponent(id, Clickable{0, 0, 100, 100});
    entities.setEntityComponent(id, COMP_CLICK);
    selectables.addComponent(id, {});
    entities.setEntityComponent(id, COMP_SELECT);
    // storeEnergy.addComponent(id, StoreEnergy{0, 100, 0, 0});
    // entities.setEntityComponent(id, COMP_STORE_E);
    light.addComponent(id, {150, 50, 50});
    entities.setEntityComponent(id, COMP_LIGHT);
}