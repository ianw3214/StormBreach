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
    for (unsigned int index = 0; index < game->getStoreEnergy().getIds().size(); index++) {
        unsigned int id = game->getStoreEnergy().getIds()[index];
        StoreEnergy& store = game->getStoreEnergy().getComponents()[index];
    }
    shader->setUniform1i("size", 10);
    DrawData data;
    data.z = 70;
    data.x = 0;
    data.y = 0;
    data.w = game->getEngineRef()->getConfig().window_width;
    data.h = game->getEngineRef()->getConfig().window_height;
    data.shader = "light";
    data.colour = Colour{1.f, 0.f, 0.f};
    data.method = DrawMethod::SQUARE;
    game->draw(data);
}