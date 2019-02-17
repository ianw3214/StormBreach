#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <array>

#include "memory/pointers.hpp"
#include "state/state.hpp"

struct EngineConfig{
    int window_width;
    int window_height;
    std::string window_name;
};

class ResourceManager;
class Renderer;
class InputHandler;

class Engine {

public:

    Engine(EngineConfig config);
    ~Engine();

    const EngineConfig& getConfig() const;
    void setState(State * state);

    Reference<ResourceManager> getResources();
    Reference<Renderer> getRenderer();
    Reference<InputHandler> getInput();

    void run();

private:
    EngineConfig m_config;
    SDL_Window * m_window;
    SDL_GLContext m_context;

    bool m_running;
    Owned<State> m_state;
    Uint32 last_time;

    // Subsystems   
    Owned<ResourceManager> m_resources;
    Owned<Renderer> m_renderer;
    Owned<InputHandler> m_input;
};