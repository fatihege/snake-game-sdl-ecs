#pragma once

#include <utility>
#include <vector>

#include "../core/Component.h"

enum class Direction {
    NONE = 0,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct SnakeComponent final : Component {
    std::vector<std::pair<int, int>> body;
    Direction direction = Direction::NONE;
    double velocity;

    SnakeComponent(): velocity(1) {
        body.emplace_back(10, 10);
    }
};