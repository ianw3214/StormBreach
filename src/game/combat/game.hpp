#pragma once

#include "state/state.hpp"
#include "components.hpp"

class Game : public State {

public:
    Game();
    ~Game();

    // Custom initialization callback
    virtual void init();

    ComponentManager<TileMap>& getTileMap();

private:
    // Additional components
    ComponentManager<TileMap> tilemap;

};