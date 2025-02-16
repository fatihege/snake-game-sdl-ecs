#include "MovementSystem.h"

#include "../Game.h"
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
                    snake->body[0].second--;
                    break;
                case Direction::DOWN:
                    snake->body[0].second++;
                    break;
                case Direction::LEFT:
                    snake->body[0].first--;
                    break;
                case Direction::RIGHT:
                    snake->body[0].first++;
                    break;
                default: ;
            }

            transform->x = snake->body[0].first;
            transform->y = snake->body[0].second;

            if (onCollision) {
                if (transform->x < 0 || transform->y < 0 || transform->x > GRID_WIDTH || transform->y > GRID_HEIGHT)
                    onCollision();

                if (std::find(snake->body.begin() + 1, snake->body.end(), std::make_pair(transform->x, transform->y))
                    != snake->body.end())
                    onCollision();
            }
        }
    }
}
