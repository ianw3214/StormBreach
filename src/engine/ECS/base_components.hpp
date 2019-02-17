#pragma once

#include <string>

#define NUM_BASE_COMPS  3
#define COMP_POS        0
#define COMP_SPRITE     1
#define COMP_CAMERA     2

struct Position {
    int x;
    int y;
    float z;
    bool camera_affect;
    Position(int x=0, int y=0, bool c=false, float z = 0) : x(x), y(y), camera_affect(c), z(z) {}
};

struct Sprite {
    int w;
    int h;
    int x_offset;
    int y_offset;
    std::string name;
    Sprite(int w=0, int h=0, int x_o=0, int y_o=0, const std::string& n="") :
        w(w), h(h), x_offset(x_o), y_offset(y_o), name(n) {}
};

#define CAM_IDLE    0
#define CAM_FREE    1
struct Camera {
    int behaviour;
    float cam_speed;
    int margin;
    Camera(int b=CAM_IDLE, float s=100.f, int m=100) : behaviour(b), cam_speed(s), margin(m) {}
};