#include "EntityManager.h"

std::vector<std::shared_ptr<Entity>> EntityManager::getEntities() {
    return entities;
}

std::shared_ptr<Entity> EntityManager::createEntity() {
    auto entity = std::make_shared<Entity>(nextEntityID++);
    entities.push_back(entity);
    return entity;
}

void EntityManager::removeInactiveEntities() {
    std::erase_if(entities, [](const std::shared_ptr<Entity> &entity) {
        return !entity->isActive();
    });
}
