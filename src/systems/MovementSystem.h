#pragma once

#include <functional>

#include "../core/System.h"

class MovementSystem final : public System {
public:
    std::function<void()> onCollision;
    void update() override;
};
