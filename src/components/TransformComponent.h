#pragma once

#include "../core/Component.h"

struct TransformComponent final : Component {
    int x, y, width, height;

    TransformComponent(const int x, const int y, const int width, const int height)
        : x(x), y(y), width(width), height(height) {
    }
};
