#include "rain.hpp"

#include "../game.hpp"

#include "engine.hpp"
#include "resource.hpp"
#include "renderer/renderer.hpp"

RainSystem::RainSystem(Reference<Game> ref) {
    game = ref;
}

#include <iostream>
void RainSystem::update(float delta) {
    for (unsigned int index = 0; index < game->getRain().getIds().size(); ++index) {
        unsigned int id = game->getRain().getIds()[index];
        RainParticles& rain = game->getRain().getComponents()[index];
        // First update the rain particles
        for (RainParticle& part : rain.particles) {
            // Initialzie the rain particle if it is not yet initialzed OR lifespan over
            if (part.lifetime == 0.f || part.elapsed > part.lifetime) {
                part.pos.x = rand() % (game->getEngineRef()->getConfig().window_width);
                // Make sure the rain spawns a bit above the screen
                part.pos.y = rand() % (game->getEngineRef()->getConfig().window_height) - 100;
                part.lifetime = static_cast<float>(rand() % 800) / 1000.f;
                part.elapsed = 0.f;
                part.speed = 400.f * static_cast<float>(rand() % 100 + 100) / 100.f;
            }
            // Then, update the rain particle
            part.pos.y += static_cast<int>(part.speed * delta);
            part.elapsed += delta;
            // Then, draw the rain particle
            DrawData data;
            data.z = 80;
            data.x = part.pos.x;
            data.y = part.pos.y;
            data.x2 = part.pos.x;
            data.y2 = part.pos.y + 20;
            data.colour = Colour{0.f, 0.5f, 1.f};
            data.method = DrawMethod::LINE;
            game->draw(data);
        }
    }
}