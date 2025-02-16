#include "CollisionSystem.h"

#include <iostream>

#include "../components/FoodComponent.h"
#include "../components/SnakeComponent.h"
#include "../components/TransformComponent.h"

void CollisionSystem::update() {
    std::vector<std::shared_ptr<Entity>> snakes;
    std::vector<std::shared_ptr<Entity>> foods;

    for (const auto &entity: entities) {
        if (entity->hasComponent<SnakeComponent>() && entity->hasComponent<TransformComponent>())
            snakes. push_back(entity);
        if (entity->hasComponent<FoodComponent>() && entity->hasComponent<TransformComponent>())
            foods.push_back(entity);
    }

    for (const auto& snake : snakes) {
        const auto snakeTransform = snake->getComponent<TransformComponent>();
        const auto snakeData = snake->getComponent<SnakeComponent>();

        for (const auto& food : foods) {
            const auto foodTransform = food->getComponent<TransformComponent>();
            const auto foodData = food->getComponent<FoodComponent>();

            if (snakeTransform->x == foodTransform->x && snakeTransform->y == foodTransform->y) {
                foodData->eaten = true;
                snakeData->body.push_back({-1, -1});
                std::cout << "Snake length: " << snakeData->body.size() << std::endl;

                food->destroy();
            }
        }
    }
}
