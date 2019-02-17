#pragma once

#include "memory/pointers.hpp"
#include "../system.hpp"

class State;
class Engine;
class CameraUpdateSystem : public System{

public:
    CameraUpdateSystem(Reference<State> ref);
    virtual void update(float delta);
private:
    Reference<State> state;
    Reference<Engine> engine;
};