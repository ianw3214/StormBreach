#pragma once

#include "opengl/glwrapper.hpp"

#define COMP_TILEMAP    NUM_BASE_COMPS + 0

struct TileMap {
    int width;
    int height;
    int tile_size;
    std::vector<int> map;
};