#version 400 core

flat in ivec2 vPosition;
out vec4 colour;

uniform int size;

void main() {

    colour = vec4(1.f, 1.f, 0.f, 1.f);

    if (size > 0) {
        colour = vec4(1.f, 1.f, 1.f, 1.f);
    }

}