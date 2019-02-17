#pragma once

#include "state/state.hpp"
#include "components.hpp"

class Game : public State {

public:
    Game();
    ~Game();

    // Custom initialization callback
    virtual void init();

    ComponentManager<TileMap>& getTileMap() { return tilemap; }
    ComponentManager<Selectable>& getSelectables() { return selectables; }
    ComponentManager<GenerateEnergy>& getGenerateEnergy() { return generateEnergy; }
    ComponentManager<StoreEnergy>& getStoreEnergy() { return storeEnergy; }
    
    ComponentManager<RainParticles>& getRain() { return rain; }

private:
    // Additional components
    ComponentManager<TileMap> tilemap;
    ComponentManager<Selectable> selectables;
    ComponentManager<GenerateEnergy> generateEnergy;
    ComponentManager<StoreEnergy> storeEnergy;

    ComponentManager<RainParticles> rain;

};