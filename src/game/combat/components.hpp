#pragma once

#include "opengl/glwrapper.hpp"
#include "util/vec.hpp"

#define COMP_TILEMAP    NUM_BASE_COMPS + 0
#define COMP_CLICK      NUM_BASE_COMPS + 1
#define COMP_SELECT     NUM_BASE_COMPS + 2
#define COMP_GEN_E      NUM_BASE_COMPS + 3
#define COMP_STORE_E    NUM_BASE_COMPS + 4
#define COMP_RAIN       NUM_BASE_COMPS + 5
#define COMP_LIGHT      NUM_BASE_COMPS + 6
#define COMP_HEALTH     NUM_BASE_COMPS + 7

struct TileMap {
    int width;
    int height;
    int tile_size;
    std::vector<int> map;
};

struct Clickable {
    int x_offset;
    int y_offset;
    int box_w;
    int box_h;
};

struct Selectable {
    bool selected;
};

struct GenerateEnergy {
    int energy_per_second;
    float time_elapsed;
};

struct StoreEnergy {
    int current_charge;
    int max_charge;
    int render_offset_x;
    int render_offset_y;
};

// This is not a component, but a thing to be stored in rainParticles component
struct RainParticle {
    Vec2i pos;
    float lifetime;
    float elapsed;
    float speed;
    RainParticle(Vec2i pos = {0, 0}, float l = 0.f, float e = 0.f, float speed = 100.f) 
        : pos(pos), lifetime(l), elapsed(e), speed(speed) {}
};
struct RainParticles {
    int max_particles;
    std::vector<RainParticle> particles;
};

struct Light {
    int radius;
    int x_offset;
    int y_offset;
};

struct Health {
    int current;
    int max;
};