#include "RenderSystem.h"

#include "../components/RenderComponent.h"
#include "../components/SnakeComponent.h"
#include "../components/TransformComponent.h"

void RenderSystem::update() {
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    for (const auto &entity: entities) {
        const auto snake = entity->getComponent<SnakeComponent>();
        const auto transform = entity->getComponent<TransformComponent>();
        const auto render = entity->getComponent<RenderComponent>();

        if (transform && render) {
            if (snake)
                for (int i = 1; i < snake->body.size(); i++) {
                    const int x = snake->body[i].first;
                    const int y = snake->body[i].second;
                    SDL_Rect rect = {x * transform->width, y * transform->height, transform->width, transform->height};
                    SDL_SetRenderDrawColor(renderer, render->color.r, render->color.g, render->color.b,
                                           render->color.a - 55);
                    SDL_RenderFillRect(renderer, &rect);
                }

            SDL_Rect rect = {
                transform->x * transform->width, transform->y * transform->height, transform->width, transform->height
            };
            SDL_SetRenderDrawColor(renderer, render->color.r, render->color.g, render->color.b, render->color.a);
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}
