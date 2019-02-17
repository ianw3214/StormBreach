#include "energy.hpp"

#include "../game.hpp"

#include "engine.hpp"
#include "resource.hpp"
#include "text/text_renderer.hpp"

EnergySystem::EnergySystem(Reference<Game> ref) {
    game = ref;
}

void EnergySystem::update(float delta) {
    game->getEngineRef()->getText()->setAlignment(TextRenderer::hAlign::left, TextRenderer::vAlign::middle);
    for (unsigned int index = 0; index < game->getStoreEnergy().getIds().size(); index++) {
        unsigned int id = game->getStoreEnergy().getIds()[index];
        StoreEnergy& store = game->getStoreEnergy().getComponents()[index];
        // If the component generates energy, check if we need to add more energy
        if (game->getEntities().entityHasComponent(id, COMP_GEN_E)) {
            GenerateEnergy& gen = *(game->getGenerateEnergy().getComponent(id));
            if (gen.time_elapsed > 1.f) {
                store.current_charge += gen.energy_per_second;
                if (store.current_charge > store.max_charge) store.current_charge = store.max_charge;
                gen.time_elapsed = 0.f;
            }
            gen.time_elapsed += delta;
        }
        // Render the energy value if there is a position to render at
        if (game->getEntities().entityHasComponent(id, COMP_POS)) {
            Position pos = *(game->getPositions().getComponent(id));
            DrawData data;
            data.z = 100;
            data.x = pos.x + store.render_offset_x;
            data.y = pos.y + store.render_offset_y;
            if (pos.camera_affect) {
                for (unsigned int c_index = 0; c_index < game->getCamera().getIds().size(); c_index++) {
                    unsigned int c_id = game->getCamera().getIds()[c_index];
                    Camera& camera = game->getCamera().getComponents()[c_index];
                    if (!(game->getEntities().entityHasComponent(c_id, COMP_CAMERA))) {
                        continue;
                    }
                    Position c_pos = *(game->getPositions().getComponent(c_id));
                    data.x -= c_pos.x;
                    data.y -= c_pos.y;
                    break;
                }
            }
            data.name = "Energy: ";
            data.name += std::to_string(store.current_charge);
            data.colour = Colour{1.f, 1.f, 1.f};
            data.scale = 0.8f;
            data.method = DrawMethod::TEXT;
            game->draw(data);
        }
    }
}