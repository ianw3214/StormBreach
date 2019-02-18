#include "light.hpp"

#include "../game.hpp"

#include "engine.hpp"
#include "resource.hpp"
#include "text/text_renderer.hpp"

LightSystem::LightSystem(Reference<Game> ref) {
    game = ref;
    ShaderRef shader = game->getEngineRef()->getResources()->loadShader("light", "res/shaders/light.vert", "res/shaders/light.frag");
    shader->setUniform1i("u_screen_width", game->getEngineRef()->getConfig().window_width);
	shader->setUniform1i("u_screen_height", game->getEngineRef()->getConfig().window_height);
}

void LightSystem::update(float delta) {
    ShaderRef shader = game->getEngineRef()->getResources()->loadShader("light", "res/shaders/light.vert", "res/shaders/light.frag");
    int counter = 0;
    for (unsigned int index = 0; index < game->getLight().getIds().size(); index++) {
        unsigned int id = game->getLight().getIds()[index];
        Light& light = game->getLight().getComponents()[index];
        if (game->getEntities().entityHasComponent(id, COMP_POS)) {
            Position pos = *(game->getPositions().getComponent(id));
            pos.x += light.x_offset;
            pos.y += light.y_offset;
            if (pos.camera_affect) {
                for (unsigned int c_index = 0; c_index < game->getCamera().getIds().size(); c_index++) {
                    unsigned int c_id = game->getCamera().getIds()[c_index];
                    Camera& camera = game->getCamera().getComponents()[c_index];
                    if (!(game->getEntities().entityHasComponent(c_id, COMP_POS))) {
                        continue;
                    }
                    Position c_pos = *(game->getPositions().getComponent(c_id));
                    pos.x -= c_pos.x;
                    pos.y -= c_pos.y;
                    break;
                }
            }
            // Set the position uniform in the shader
            std::string base = std::string("lights[") + std::to_string(counter) + std::string("]");
            shader->setUniform1i(base + std::string(".x"), pos.x);
            shader->setUniform1i(base + std::string(".y"), pos.y);
            shader->setUniform1i(base + std::string(".r"), light.radius);
            counter++;
        }
    }
    
    shader->setUniform1i("size", counter);
    DrawData data;
    data.z = 85;
    data.x = 0;
    data.y = 0;
    data.w = game->getEngineRef()->getConfig().window_width;
    data.h = game->getEngineRef()->getConfig().window_height;
    data.shader = "light";
    data.colour = Colour{1.f, 0.f, 0.f};
    data.method = DrawMethod::SQUARE;
    game->draw(data);
}