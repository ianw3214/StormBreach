#pragma once

#include "opengl/glwrapper.hpp"

#define COMP_TILEMAP    NUM_BASE_COMPS + 0
#define COMP_SELECT     NUM_BASE_COMPS + 1

struct TileMap {
    int width;
    int height;
    int tile_size;
    std::vector<int> map;
};

struct Selectable {
    bool selected;
    int x_offset;
    int y_offset;
    int box_w;
    int box_h;
};