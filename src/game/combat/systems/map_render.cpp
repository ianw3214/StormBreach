#include "map_render.hpp"

#include "../game.hpp"

#include "engine.hpp"
#include "resource.hpp"
#include "renderer/renderer.hpp"

MapRenderSystem::MapRenderSystem(Reference<Game> ref) {
    game = ref;
    // Initialize tile sprites
    palette.emplace_back("base", "res/tiles/base.png");
    // Load the textures
    for (const PaletteData tile : palette) {
        game->getEngineRef()->getResources()->loadTexture(tile.name, tile.path);
    }
}

void MapRenderSystem::update(float delta) {
    for (unsigned int index = 0; index < game->getTileMap().getIds().size(); ++index) {
        unsigned int id = game->getTileMap().getIds()[index];
        TileMap& tilemap = game->getTileMap().getComponents()[index];

        if (!(game->getEntities().entityHasComponent(id, COMP_POS))) {
            continue;
        }

        Position pos = *(game->getPositions().getComponent(id));

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

        for (unsigned int i = 0; i < tilemap.map.size(); ++i) {
            int x = (i % tilemap.width) * tilemap.tile_size + pos.x;
            int y = (i / tilemap.width) * tilemap.tile_size + pos.y;
            if (tilemap.map[i] >= static_cast<int>(palette.size()) || tilemap.map[i] < 0) {
                // Render random square if not valid
                DrawData data;
                data.z = -1;
                data.x = x;
                data.y = y;
                data.w = tilemap.tile_size;
                data.h = tilemap.tile_size;
                data.colour = Colour{1.f, 0.f, 1.f};
                data.method = DrawMethod::SQUARE;
                game->draw(data);
            } else {
                DrawData data;
                data.z = -1;
                data.x = x;
                data.y = y;
                data.w = tilemap.tile_size;
                data.h = tilemap.tile_size;
                data.src_x = 0;
                data.src_y = 0;
                if (game->getEngineRef()->getResources()->getTexture(palette[tilemap.map[i]].name)) {
                    data.src_w = game->getEngineRef()->getResources()->getTexture(palette[tilemap.map[i]].name)->getWidth();
                    data.src_h = game->getEngineRef()->getResources()->getTexture(palette[tilemap.map[i]].name)->getHeight();
                }
                data.name = palette[tilemap.map[i]].name;
                data.method = DrawMethod::TEXTURE;
                game->draw(data);
            }
        }
    }
}