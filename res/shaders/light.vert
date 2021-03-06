#version 400 core

layout(location = 0) in ivec2 position;

out vec2 vPosition;

uniform int u_screen_width;
uniform int u_screen_height;

void main() {
    float x = mix(-1.0f, 1.0f, float(position.x) / float(u_screen_width));
    float y = mix(-1.0f, 1.0f, float(position.y) / float(u_screen_height));

    // Invert y so that the origin is on the top left corner
    gl_Position = vec4(x, -y, 0.f, 1.0f);

    vPosition = vec2(float(position.x), float(position.y));
}