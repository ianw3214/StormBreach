#pragma once

#include "state/state.hpp"
#include "components.hpp"

#include "ui/button.hpp"

enum class BuildTarget {
    PLANT,
    FACTORY,
    ERROR
};

// Aight I'm hard coding shit cause deadline's almost up
struct Enemy {
    int x;
    int y;
    int health;
    unsigned int target_id;
    int offset_x;
    int offset_y;
    bool attacking;
    float attack_timer;
};

class Game : public State {

public:
    Game();
    ~Game();

    // Custom initialization callback
    virtual void init();

    ComponentManager<TileMap>& getTileMap() { return tilemap; }
    ComponentManager<Clickable>& getClickables() { return clickables; }
    ComponentManager<Selectable>& getSelectables() { return selectables; }
    ComponentManager<GenerateEnergy>& getGenerateEnergy() { return generateEnergy; }
    ComponentManager<StoreEnergy>& getStoreEnergy() { return storeEnergy; }
    ComponentManager<Health>& getHealth() { return health; }
    
    ComponentManager<RainParticles>& getRain() { return rain; }
    ComponentManager<Light>& getLight() { return light; }

    bool show_build_menu;
    int menu_x, menu_y;
    bool building;
    BuildTarget build_target;
    Button& getBuildPlantButton() { return build_plant_button; }
    Button& getBuildFactoryButton() { return build_factory_button; }

    void addPlant(int x, int y);
    void addFactory(int x, int y);

    std::vector<Enemy> enemies;

private:
    // Additional components
    ComponentManager<TileMap> tilemap;

    ComponentManager<Clickable> clickables;
    ComponentManager<Selectable> selectables;
    ComponentManager<GenerateEnergy> generateEnergy;
    ComponentManager<StoreEnergy> storeEnergy;
    ComponentManager<Health> health;

    ComponentManager<RainParticles> rain;
    ComponentManager<Light> light;

    Button build_plant_button;
    Button build_factory_button;

};