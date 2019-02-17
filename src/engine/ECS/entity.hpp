#pragma once

#include <vector>
#include <unordered_map>

#include "util/bitarray.hpp"

class Entity {
public:
    Entity(unsigned int id=0) : m_id(id) {}
    unsigned int getId() const { return m_id; }

    void setComponentBit(unsigned int bit) { bits |= bit; }
    bool hasComponent(unsigned int bit) { return bits | bit; }
private:
    unsigned int m_id;
    BitArray bits;
};

class EntityManager {
public:
    EntityManager();

    unsigned int addEntity();
    // TODO: (Ian) Remove entity functionality

    void setEntityComponent(unsigned int entity, unsigned int bit);
    bool entityHasComponent(unsigned int entity, unsigned int bit);
private:
    // Keep a list of entities in sorted order
    std::vector<Entity> entities;
    // Keep a list of IDs to assign to the next entity
    unsigned int current_id;
};