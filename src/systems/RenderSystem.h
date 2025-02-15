#pragma once

#include <SDL_render.h>

#include "../core/System.h"

class RenderSystem final : public System {
    SDL_Renderer *renderer = nullptr;

public:
    explicit RenderSystem(SDL_Renderer* renderer) : renderer(renderer) {}

    void update() override;
};
