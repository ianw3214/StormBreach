#include "button.hpp"

Button::Button(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {

}

Button::~Button() {

}

bool Button::over_button(int t_x, int t_y) const {
    return t_x > x && t_x < x + w && t_y > y && t_y < y + h;
}