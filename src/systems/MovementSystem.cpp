#include "MovementSystem.h"

#include "../components/SnakeComponent.h"
#include "../components/TransformComponent.h"

void MovementSystem::update() {
    for (const auto &entity: entities) {
        const auto snake = entity->getComponent<SnakeComponent>();
        const auto transform = entity->getComponent<TransformComponent>();

        if (snake && transform) {
            for (int i = snake->body.size() - 1; i > 0; i--) snake->body[i] = snake->body[i - 1];

            switch (snake->direction) {
                case Direction::UP:
                    snake->body[0].second -= snake->velocity;
                    break;
                case Direction::DOWN:
                    snake->body[0].second += snake->velocity;
                    break;
                case Direction::LEFT:
                    snake->body[0].first -= snake->velocity;
                    break;
                case Direction::RIGHT:
                    snake->body[0].first += snake->velocity;
                    break;
                default: ;
            }

            transform->x = snake->body[0].first;
            transform->y = snake->body[0].second;
        }
    }
}
