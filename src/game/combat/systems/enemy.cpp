#include "enemy.hpp"

#include "../game.hpp"
#include "engine.hpp"
#include "resource.hpp"
#include "renderer/renderer.hpp"

constexpr int enemy_cap = 10;
constexpr float speed = 200.f;
constexpr float attack_interval = 2.5f;

EnemySystem::EnemySystem(Reference<Game> ref) {
    game = ref;
    game->getEngineRef()->getResources()->loadTexture("enemy", "res/units/enemy.png");
    game->getEngineRef()->getResources()->loadTexture("enemy_attack", "res/units/enemy_attack.png");
}

#include <iostream>
void EnemySystem::update(float delta) {
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
    // Spawn enemies if needed
    if (game->enemies.size() < enemy_cap) {
        int key = rand() % 120;
        if (key < 1 || game->enemies.size() < 2) {
            Enemy enemy;
            enemy.x = rand() % 1200;
            enemy.y = rand() % 1200 - 200;
            enemy.health = 10;
            enemy.target_id = findTarget();
            enemy.offset_x = rand() % 100 - 50;
            enemy.offset_y = rand() % 100 - 50;
            enemy.attacking = false;
            enemy.attack_timer = 0.f;
            game->enemies.push_back(enemy);
        }
    }
    for (Enemy& e : game->enemies) {
        // Update enemies
        {   // Get the position of the target and try to move towards it
            if (game->getEntities().entityHasComponent(e.target_id, COMP_POS)) {
                if (!e.attacking) {
                    Position target = *(game->getPositions().getComponent(e.target_id));
                    int distance = static_cast<int>(speed * delta);
                    int target_x = target.x + e.offset_x;
                    int target_y = target.y + e.offset_y;
                    if (e.x < target_x) {
                        e.x += distance;
                        if (e.x > target.x) e.x = target_x;
                    }
                    if (e.x > target_x) {
                        e.x -= distance;
                        if (e.x < target_x) e.x = target_x;
                    }
                    if (e.y < target_y) {
                        e.y += distance;
                        if (e.y > target_y) e.y = target_y;
                    }
                    if (e.y > target_y) {
                        e.y -= distance;
                        if (e.y < target_y) e.y = target_y;
                    }
                    if (e.x == target_x && e.y == target_y) e.attacking = true;
                } else {
                    if (e.attack_timer > attack_interval) {
                        e.attack_timer = 0.f;
                        Health& health = *(game->getHealth().getComponent(e.target_id));
                        if (health.current > 0) health.current--;
                        else {
                            e.target_id = findTarget();
                            e.attacking = false;
                        }
                    } else {
                        e.attack_timer += delta;
                    }
                }
            } else {
                e.target_id = findTarget();
            }
        }
        // Render enemies
        DrawData data;
        data.z = 10;
        data.x = e.x - cam_x;
        data.y = e.y - cam_y;
        data.w = 80;
        data.h = 80;
        data.src_x = 0;
        data.src_y = 0;
        data.src_w = 80;
        data.src_h = 80;
        data.name = e.attacking ? "enemy_attack" : "enemy";
        data.method = DrawMethod::TEXTURE;
        game->draw(data);
    }
}

unsigned int EnemySystem::findTarget() {
    unsigned int num_comps = game->getHealth().getIds().size();
    return game->getHealth().getIds()[rand() % num_comps];
}