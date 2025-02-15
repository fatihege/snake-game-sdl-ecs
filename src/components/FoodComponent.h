#pragma once

#include "../core/Component.h"

struct FoodComponent final : Component {
    bool eaten = false;
};