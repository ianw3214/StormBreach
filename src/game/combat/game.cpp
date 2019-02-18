#include "game.hpp"

#include "engine.hpp"
#include "resource.hpp"
#include "systems/systems.hpp"

Game::Game() {

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
        unsigned int id = addEntity();
        positions.addComponent(id, Position(200, 200, true, 1));
        entities.setEntityComponent(id, COMP_POS);
        sprites.addComponent(id, Sprite(100, 100, 0, 0, "plant"));
        entities.setEntityComponent(id, COMP_SPRITE);
        selectables.addComponent(id, Selectable{false, 0, 0, 100, 100});
        entities.setEntityComponent(id, COMP_SELECT);
        generateEnergy.addComponent(id, GenerateEnergy{5});
        entities.setEntityComponent(id, COMP_GEN_E);
        storeEnergy.addComponent(id, StoreEnergy{0, 100, 0, 0});
        entities.setEntityComponent(id, COMP_STORE_E);
        light.addComponent(id, {150, 50, 50});
        entities.setEntityComponent(id, COMP_LIGHT);
    }
    {   // Starting factory
        unsigned int id = addEntity();
        positions.addComponent(id, Position(300, 300, true, 1));
        entities.setEntityComponent(id, COMP_POS);
        sprites.addComponent(id, Sprite(100, 100, 0, 0, "factory"));
        entities.setEntityComponent(id, COMP_SPRITE);
        selectables.addComponent(id, Selectable{false, 0, 0, 100, 100});
        entities.setEntityComponent(id, COMP_SELECT);
        // storeEnergy.addComponent(id, StoreEnergy{0, 100, 0, 0});
        // entities.setEntityComponent(id, COMP_STORE_E);
        light.addComponent(id, {150, 50, 50});
        entities.setEntityComponent(id, COMP_LIGHT);
    }

}