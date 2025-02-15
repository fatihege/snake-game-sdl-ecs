#pragma once

#include <memory>
#include <vector>

#include "Entity.h"

class System {
protected:
    std::vector<std::shared_ptr<Entity>> entities;

public:
    virtual ~System() = default;

    void addEntity(const std::shared_ptr<Entity> &entity) {
        entities.push_back(entity);
    }

    void removeEntity(const std::shared_ptr<Entity> &entity) {
        std::erase(entities, entity);
    }

    virtual void update() = 0;
};
