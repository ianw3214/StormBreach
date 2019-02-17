#include "engine.hpp"

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include <ctime>

#include "resource.hpp"
#include "renderer/renderer.hpp"
#include "input/input.hpp"
#include "text/text_renderer.hpp"

// Restrict the engine to 120 fps
const float min_update_time = 1.f / 120.f;

Engine::Engine(EngineConfig config) : m_config(config), m_running(true) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) exit(1);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    SDL_GL_SetSwapInterval(1);

    int w = m_config.window_width;
    int h = m_config.window_height;
    const char * name = m_config.window_name.c_str();
    
    m_window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_OPENGL);
    if (m_window == nullptr) exit(1);
    m_context = SDL_GL_CreateContext(m_window);
    if (m_context == NULL) exit(1);

    glClearDepth(-1.f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_GEQUAL);

    // Glew can only be initialized after a valid openGL context is created
    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) exit(1);

    // Initialize subsystems once a valid openGL context is created
    m_resources = new ResourceManager();
    m_renderer = new Renderer(this);
    m_input = new InputHandler();
    m_text = new TextRenderer("res/fonts/AllerDisplay.ttf", 32, Vec2i{config.window_width, config.window_height});

    srand(static_cast<unsigned int>(time(nullptr)));
}

Engine::~Engine() {
    // Not actually too important, OS will take care of it
}

const EngineConfig& Engine::getConfig() const {
    return m_config;
}

void Engine::setState(State * state) {
    m_state = state;
    m_state->setEngineRef(this);
    m_state->base_init();
}

Reference<ResourceManager> Engine::getResources() {
    return Reference<ResourceManager>(m_resources);
}

Reference<Renderer> Engine::getRenderer() {
    return Reference<Renderer>(m_renderer);
}

Reference<InputHandler> Engine::getInput() {
    return Reference<InputHandler>(m_input);
}

Reference<TextRenderer> Engine::getText() {
    return Reference<TextRenderer>(m_text);
}

void Engine::run() {
    last_time = SDL_GetTicks();
    while(m_running) {
        // Delta time calculations
        Uint32 curr_time = SDL_GetTicks();
        float delta = static_cast<float>(curr_time - last_time) / 1000.f;
        if (delta < min_update_time) continue;
        last_time = curr_time;

        m_renderer->clear();

        m_input->update();
        m_state->update(delta);

        SDL_GL_SwapWindow(m_window);
    }
}