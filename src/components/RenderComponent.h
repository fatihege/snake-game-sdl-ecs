#pragma once

#include <SDL2/SDL.h>

#include "../core/Component.h"

struct RenderComponent final : Component {
    SDL_Color color;

    explicit RenderComponent(const SDL_Color c) : color(c) {
    }
};
