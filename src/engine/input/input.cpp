#include "input.hpp"

InputHandler::InputHandler() {
    
}

InputHandler::~InputHandler() {

}

void InputHandler::update() {
    // Reset variables that need to be reset
    mouse_down = false;
    mouse_up = false;
    SDL_GetMouseState(&mouse_x, &mouse_y);
    // Poll for events
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        // Always quit on exit
        if (e.type == SDL_QUIT) {
            exit(0);
        }
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            mouse_down = true;
            mouse_held = true;
        }
        if (e.type == SDL_MOUSEBUTTONUP) {
            mouse_up = true;
            mouse_held = false;
        }
    }
}

bool InputHandler::is_mouse_down() const {
    return mouse_down;
}
bool InputHandler::is_mouse_up() const {
    return mouse_up;
}
bool InputHandler::is_mouse_held() const {
    return mouse_held;
}
int InputHandler::get_mouse_x() const {
    return mouse_x;
}
int InputHandler::get_mouse_y() const {
    return mouse_y;
}