#include "health.hpp"

#include "../game.hpp"
#include "engine.hpp"

HealthSystem::HealthSystem(Reference<Game> ref) {
    game = ref;
    game->getEngineRef()->getResources()->loadTexture("health", "res/health.png");
}

// Just handles rendering
void HealthSystem::update(float delta) {
    int cam_x = 0;
    int cam_y = 0;
    for (unsigned int c_index = 0; c_index < game->getCamera().getIds().size(); c_index++) {
        unsigned int c_id = game->getCamera().getIds()[c_index];
        Camera& camera = game->getCamera().getComponents()[c_index];
        if (!(game->getEntities().entityHasComponent(c_id, COMP_CAMERA))) {
            continue;
        }
        Position c_pos = *(game->getPositions().getComponent(c_id));
        cam_x = c_pos.x;
        cam_y = c_pos.y;
        break;
    }
    for (unsigned int index = 0; index < game->getHealth().getComponents().size(); ++index) {
        unsigned int id = game->getHealth().getIds()[index];
        Health health = game->getHealth().getComponents()[index];
        // Make sure there is a position attribute to render the health
        if (game->getEntities().entityHasComponent(id, COMP_POS)) {
            Position pos = *(game->getPositions().getComponent(id));
            for (int i = 0; i < health.current; ++i) {
                DrawData data;
                data.z = 200;
                data.x = pos.x + i * 14 - cam_x;
                data.y = pos.y - cam_y + 100;
                data.w = 12;
                data.h = 20;
                data.src_x = 0;
                data.src_y = 0;
                data.src_w = 12;
                data.src_h = 20;
                data.name = "health";
                data.method = DrawMethod::TEXTURE;
                game->draw(data);
            }
        }
    }
}