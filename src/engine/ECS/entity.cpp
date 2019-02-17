#include "entity.hpp"

EntityManager::EntityManager() {
    entities.reserve(30);
    current_id = 0;
}

unsigned int EntityManager::addEntity() {
    unsigned int temp = current_id;
    entities.emplace_back(current_id);
    current_id++;
    return temp;
}

void EntityManager::setEntityComponent(unsigned int entity, unsigned int bit) {
    // Do a binary search on m_ids to find the right component
    int mid, low = 0, high = entities.size() - 1;
    int result = -1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (entities[mid].getId() > entity)
            high = mid -1;
        else if (entities[mid].getId() < entity)
            low = mid + 1;
        else {
            result = mid;
            break;
        }
    }
    if (result < 0) {
        return;
    }
    entities[result].setComponentBit(bit);
}

bool EntityManager::entityHasComponent(unsigned int entity, unsigned int bit) {
    // Do a binary search on m_ids to find the right component
    int mid, low = 0, high = entities.size() - 1;
    int result = -1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (entities[mid].getId() > entity)
            high = mid -1;
        else if (entities[mid].getId() < entity)
            low = mid + 1;
        else {
            result = mid;
            break;
        }
    }
    if (result < 0) {
        return false;
    }
    return entities[result].hasComponent(bit);
}