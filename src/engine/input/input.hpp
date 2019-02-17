#pragma once

#include <SDL2/SDL.h>

class InputHandler{
public:
    
    InputHandler();
    ~InputHandler();

    void update();

    bool is_mouse_down() const;
    bool is_mouse_up() const;
    bool is_mouse_held() const;
    int get_mouse_x() const;
    int get_mouse_y() const;

private:

    bool mouse_down;
    bool mouse_up;
    bool mouse_held;

    int mouse_x, mouse_y;

};