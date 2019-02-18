#version 400 core

in vec2 vPosition;
out vec4 colour;

struct light {
    int x;
    int y;
    int r;
};
#define MAX_LIGHTS 128
uniform int size;
uniform light lights[MAX_LIGHTS];

void main() {

    float alpha = 1.f;
    for (int i = 0; i < size; ++i) {
        float a = abs(vPosition.x - float(lights[i].x));
        float b = abs(vPosition.y - float(lights[i].y));
        float f = 1.f - (a * a + b * b) / (lights[i].r * lights[i].r);
        if (f < 0.f) continue;
        alpha -= sqrt(f);
        if (alpha < 0.f) {
            alpha = 0.f;
            break;
        }
    }

    colour = vec4(0.f, 0.f, 0.f, alpha);

}