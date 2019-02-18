#pragma once

class Button {

public:

    Button(int x, int y, int w, int h);
    ~Button();

    void set_x(int new_x) { x = new_x; }
    void set_y(int new_y) { y = new_y; }

    int get_x() const { return x; }
    int get_y() const { return y; }
    int get_w() const { return w; }
    int get_h() const { return h; }

    bool over_button(int x, int y) const;

private:
    int x, y;
    int w, h;
};