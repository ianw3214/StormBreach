#include "camera_update.hpp"

#include "engine.hpp"
#include "renderer/renderer.hpp"
#include "input/input.hpp"

#include "state/state.hpp"

#include <iostream>

CameraUpdateSystem::CameraUpdateSystem(Reference<State> ref) {
    state = ref;
    engine = state->getEngineRef();
}

void CameraUpdateSystem::update(float delta) {
    for (unsigned int index = 0; index < state->getCamera().getIds().size(); index++) {

        unsigned int id = state->getCamera().getIds()[index];
        Camera& camera = state->getCamera().getComponents()[index];
        if (!(state->getEntities().entityHasComponent(id, COMP_POS))) {
            continue;
        }
        Position& pos = *(state->getPositions().getComponent(id));
        
        // Update camera based on behaviour
        if (camera.behaviour == CAM_IDLE) {
            // No change in position
        }
        if (camera.behaviour == CAM_FREE) {
            // Update camera position based on mouse position
            int x = engine->getInput()->get_mouse_x();
            int y = engine->getInput()->get_mouse_y();
            int w = engine->getConfig().window_width;
            int h = engine->getConfig().window_height;
            if (x < camera.margin) {
                pos.x -= static_cast<int>(camera.cam_speed * delta);
            }
            if (x > w - camera.margin) {
                pos.x += static_cast<int>(camera.cam_speed * delta);
            }
            if (y < camera.margin) {
                pos.y -= static_cast<int>(camera.cam_speed * delta);
            }
            if (y > h - camera.margin) {
                pos.y += static_cast<int>(camera.cam_speed * delta);
            }
        }

    }
}