#include "sprite_render.hpp"

#include "engine.hpp"
#include "resource.hpp"
#include "renderer/renderer.hpp"

#include "state/state.hpp"

#include <iostream>

SpriteRenderSystem::SpriteRenderSystem(Reference<State> ref) {
    state = ref;
    engine = state->getEngineRef();
}

void SpriteRenderSystem::update(float delta) {
    for (unsigned int index = 0; index < state->getSprites().getIds().size(); index++) {
        unsigned int id = state->getSprites().getIds()[index];
        Sprite& sprite = state->getSprites().getComponents()[index];
        if (!(state->getEntities().entityHasComponent(id, COMP_POS))) {
            continue;
        }
        Position pos = *(state->getPositions().getComponent(id));
        int x = pos.x + sprite.x_offset;
        int y = pos.y + sprite.y_offset;
        if (pos.camera_affect) {
            for (unsigned int c_index = 0; c_index < state->getCamera().getIds().size(); c_index++) {
                unsigned int c_id = state->getCamera().getIds()[c_index];
                Camera& camera = state->getCamera().getComponents()[c_index];
                if (!(state->getEntities().entityHasComponent(c_id, COMP_CAMERA))) {
                    continue;
                }
                Position c_pos = *(state->getPositions().getComponent(c_id));
                x -= c_pos.x;
                y -= c_pos.y;
                break;
            }
        }
        DrawData data;
        data.z = pos.z;
        data.x = x;
        data.y = y;
        data.w = sprite.w;
        data.h = sprite.h;
        data.src_x = 0;
        data.src_y = 0;
        if (engine->getResources()->getTexture(sprite.name)) {
            data.src_w = engine->getResources()->getTexture(sprite.name)->getWidth();
            data.src_h = engine->getResources()->getTexture(sprite.name)->getHeight();
        }
        data.name = sprite.name;
        data.method = DrawMethod::TEXTURE;
        state->draw(data);
    }
}