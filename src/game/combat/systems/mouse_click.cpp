#include "mouse_click.hpp"

#include "../game.hpp"
#include "engine.hpp"
#include "input/input.hpp"

MouseClickSystem::MouseClickSystem(Reference<Game> ref) {
    game = ref;
}

#include <iostream>
void MouseClickSystem::update(float delta) {
    bool mouse_clicked = false;
    bool select_nothing = true;
    for (unsigned int index = 0; index < game->getSelectables().getComponents().size(); ++index) {
        unsigned int id = game->getSelectables().getIds()[index];
        Selectable& selectable = game->getSelectables().getComponents()[index];
        if (game->getEntities().entityHasComponent(id, COMP_POS)) {
            Position pos = *(game->getPositions().getComponent(id));
            int x = pos.x + selectable.x_offset;
            int y = pos.y + selectable.y_offset;
            if (pos.camera_affect) {
                for (unsigned int c_index = 0; c_index < game->getCamera().getIds().size(); c_index++) {
                    unsigned int c_id = game->getCamera().getIds()[c_index];
                    Camera& camera = game->getCamera().getComponents()[c_index];
                    if (!(game->getEntities().entityHasComponent(c_id, COMP_CAMERA))) {
                        continue;
                    }
                    Position c_pos = *(game->getPositions().getComponent(c_id));
                    x -= c_pos.x;
                    y -= c_pos.y;
                    break;
                }
            }
            int w = selectable.box_w;
            int h = selectable.box_h;
            // If the mouse is clicked, handle it
            if (game->getEngineRef()->getInput()->is_mouse_down()) {
                mouse_clicked = true;
                // Check for collisions against the component if the mouse is down
                int m_x = game->getEngineRef()->getInput()->get_mouse_x();
                int m_y = game->getEngineRef()->getInput()->get_mouse_y();
                if (m_x > x && m_x < x + w && m_y > y && m_y < y + h) {
                    selectable.selected = !selectable.selected;
                    select_nothing = false;
                }
            }
        }
        // No need to handle if there is no position component
    }
    for (unsigned int index = 0; index < game->getSelectables().getComponents().size(); ++index) {
        unsigned int id = game->getSelectables().getIds()[index];
        Selectable& selectable = game->getSelectables().getComponents()[index];
        if (game->getEntities().entityHasComponent(id, COMP_POS)) {
            Position pos = *(game->getPositions().getComponent(id));
            int x = pos.x + selectable.x_offset;
            int y = pos.y + selectable.y_offset;
            if (pos.camera_affect) {
                for (unsigned int c_index = 0; c_index < game->getCamera().getIds().size(); c_index++) {
                    unsigned int c_id = game->getCamera().getIds()[c_index];
                    Camera& camera = game->getCamera().getComponents()[c_index];
                    if (!(game->getEntities().entityHasComponent(c_id, COMP_CAMERA))) {
                        continue;
                    }
                    Position c_pos = *(game->getPositions().getComponent(c_id));
                    x -= c_pos.x;
                    y -= c_pos.y;
                    break;
                }
            }
            int w = selectable.box_w;
            int h = selectable.box_h;
            // Either draw selected entities or deselec them
            if (mouse_clicked && select_nothing) {
                selectable.selected = false;
            }
            // Otherwise, just draw the selected sprites
            if (selectable.selected) {
                DrawData data;
                data.z = 10;
                data.x = x;
                data.y = y;
                data.w = w;
                data.h = h;
                data.colour = Colour{1.f, 1.f, 1.f};
                data.method = DrawMethod::SQUARE_OUTLINE;
                game->draw(data);
            }
        }
        // No need to handle if there is no position component
    }
}