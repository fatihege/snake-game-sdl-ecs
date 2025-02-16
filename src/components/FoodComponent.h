#pragma once

#include "../core/Component.h"

struct FoodComponent final : Component {
    bool special = false;
    float timer;

    explicit FoodComponent(const bool special, const float timer = 0.0f)
        : special(special), timer(timer) {}
};