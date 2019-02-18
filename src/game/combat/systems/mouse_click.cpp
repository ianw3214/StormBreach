#include "mouse_click.hpp"

#include "../game.hpp"
#include "engine.hpp"
#include "input/input.hpp"

MouseClickSystem::MouseClickSystem(Reference<Game> ref) {
    game = ref;
    game->getEngineRef()->getResources()->loadTexture("factory_blueprint", "res/units/factory_blueprint.png");
    game->getEngineRef()->getResources()->loadTexture("power_plant_blueprint", "res/units/power_plant_blueprint.png");
}

#include <iostream>
void MouseClickSystem::update(float delta) {
    int m_x = game->getEngineRef()->getInput()->get_mouse_x();
    int m_y = game->getEngineRef()->getInput()->get_mouse_y();
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
    bool mouse_clicked = game->getEngineRef()->getInput()->is_mouse_down();
    bool select_nothing = true;
    bool built = false;
    // CHECK THE BUTTONS FIRST
    if (mouse_clicked) {
        // If building, just handle that only
        if (game->building) {
            built = true;
            if (game->build_target == BuildTarget::PLANT) {
                game->addPlant(m_x + cam_x, m_y + cam_y);
            }
            game->building = false;
            if (game->build_target == BuildTarget::FACTORY) {
                game->addFactory(m_x + cam_x, m_y + cam_y);
            }
        }
        bool ui_clicked = false;
        if (game->show_build_menu) {
            if (game->getBuildPlantButton().over_button(m_x, m_y)) {
                ui_clicked = true;
                // Mouse clicked -> want to build a plant
                game->building = true;
                game->build_target = BuildTarget::PLANT;
            }
            if (game->getBuildFactoryButton().over_button(m_x, m_y)) {
                ui_clicked = true;
                // Mouse clicked -> want to build a factory
                game->building = true;
                game->build_target = BuildTarget::FACTORY;
            }
        }
        if (!ui_clicked) {
            // Check clickable components
            for (unsigned int index = 0; index < game->getClickables().getComponents().size(); ++index) {
                unsigned int id = game->getClickables().getIds()[index];
                Clickable& clickable = game->getClickables().getComponents()[index];
                if (game->getEntities().entityHasComponent(id, COMP_POS)) {
                    Position pos = *(game->getPositions().getComponent(id));
                    int x = pos.x + clickable.x_offset;
                    int y = pos.y + clickable.y_offset;
                    if (pos.camera_affect) {
                        x -= cam_x;
                        y -= cam_y;
                    }
                    int w = clickable.box_w;
                    int h = clickable.box_h;
                    // Check for collisions against the component if the mouse is down
                    if (m_x > x && m_x < x + w && m_y > y && m_y < y + h) {
                        // If the entity is selectable, select it
                        if (game->getEntities().entityHasComponent(id, COMP_SELECT)) {
                            Selectable& selectable = *(game->getSelectables().getComponent(id));
                            selectable.selected = !selectable.selected;
                            select_nothing = false;
                            // If somthing was selected, don't render the build menu
                            game->show_build_menu = false;
                        }
                    }
                }
                // No need to handle if there is no position component
            }
        }
    }
    // Render selected things
    for (unsigned int index = 0; index < game->getSelectables().getComponents().size(); ++index) {
        unsigned int id = game->getSelectables().getIds()[index];
        Selectable& selectable = game->getSelectables().getComponents()[index];
        if (game->getEntities().entityHasComponent(id, COMP_POS)) {
            if (!game->getEntities().entityHasComponent(id, COMP_CLICK)) continue;
            Clickable click = *(game->getClickables().getComponent(id));
            Position pos = *(game->getPositions().getComponent(id));
            int x = pos.x + click.x_offset;
            int y = pos.y + click.y_offset;
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
            int w = click.box_w;
            int h = click.box_h;
            // Either draw selected entities or deselect them
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
    // If nothing was clicked, then show the build menu
    if (mouse_clicked && select_nothing && !built) {
        game->show_build_menu = !game->show_build_menu;
        int current_y = m_y;
        game->getBuildPlantButton().set_x(m_x);
        game->getBuildPlantButton().set_y(current_y);
        current_y += game->getBuildPlantButton().get_h();
        game->getBuildFactoryButton().set_x(m_x);
        game->getBuildFactoryButton().set_y(current_y);
    }
    if (game->show_build_menu) renderBuildButtons(m_x, m_y);
    if (game->building) renderBlueprint(m_x, m_y);
}

void MouseClickSystem::renderBuildButtons(int m_x, int m_y) {
    bool build_plant_hover = game->getBuildPlantButton().over_button(m_x, m_y);
    bool build_factory_hover = game->getBuildFactoryButton().over_button(m_x, m_y);
    // Render the buttons always
    {   // Build plant button
        DrawData data;
        data.z = 200;
        data.x = game->getBuildPlantButton().get_x();
        data.y = game->getBuildPlantButton().get_y();
        data.w = game->getBuildPlantButton().get_w();
        data.h = game->getBuildPlantButton().get_h();
        data.colour = build_plant_hover ? Colour{.3f, .4f, .8f} : Colour{.2f, .3f, .7f};
        data.method = DrawMethod::SQUARE;
        game->draw(data);
    }
    {   // Build factory button
        DrawData data;
        data.z = 200;
        data.x = game->getBuildFactoryButton().get_x();
        data.y = game->getBuildFactoryButton().get_y();
        data.w = game->getBuildFactoryButton().get_w();
        data.h = game->getBuildFactoryButton().get_h();
        data.colour = build_factory_hover ? Colour{.3f, .4f, .8f} : Colour{.2f, .3f, .7f};
        data.method = DrawMethod::SQUARE;
        game->draw(data);
    }
    {   // Build plant text
        DrawData data;
        data.z = 201;
        data.x = game->getBuildPlantButton().get_x() + 10;
        data.y = game->getBuildPlantButton().get_y() + 20;
        data.name = "Plant";
        data.colour = Colour{1.f, 1.f, 1.f};
        data.scale = 1.f;
        data.method = DrawMethod::TEXT;
        game->draw(data);
    }
    {   // Build plant text
        DrawData data;
        data.z = 201;
        data.x = game->getBuildFactoryButton().get_x() + 10;
        data.y = game->getBuildFactoryButton().get_y() + 20;
        data.name = "Factory";
        data.colour = Colour{1.f, 1.f, 1.f};
        data.scale = 1.f;
        data.method = DrawMethod::TEXT;
        game->draw(data);
    }
}

void MouseClickSystem::renderBlueprint(int m_x, int m_y) {
    DrawData data;
    data.z = 180;
    data.x = m_x;
    data.y = m_y;
    if (game->build_target == BuildTarget::PLANT) {
        data.w = 100;
        data.h = 100;
        data.src_x = 0;
        data.src_y = 0;
        data.src_w = 100;
        data.src_h = 100;
        data.name = "power_plant_blueprint";
    }
    if (game->build_target == BuildTarget::FACTORY) {
        data.w = 100;
        data.h = 100;
        data.src_x = 0;
        data.src_y = 0;
        data.src_w = 100;
        data.src_h = 100;
        data.name = "factory_blueprint";
    }
    data.method = DrawMethod::TEXTURE;
    game->draw(data);
}