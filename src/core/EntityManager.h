#pragma once

#include <memory>
#include <vector>

#include "Entity.h"

class EntityManager {
    std::vector<std::shared_ptr<Entity>> entities;
    int nextEntityID = 0;

public:
    std::vector<std::shared_ptr<Entity>> getEntities();
    std::shared_ptr<Entity> createEntity();
    void removeInactiveEntities();
};
