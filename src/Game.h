#pragma once

#include <queue>
#include <SDL_render.h>
#include <SDL_video.h>

#include "components/SnakeComponent.h"
#include "core/EntityManager.h"
#include "systems/CollisionSystem.h"
#include "systems/MovementSystem.h"
#include "systems/RenderSystem.h"

enum class Direction;
constexpr int GRID_WIDTH = 30;
constexpr int GRID_HEIGHT = 30;
constexpr int CELL_WIDTH = 20;
constexpr int CELL_HEIGHT = 20;

class Game {
    bool running = false;
    float dt = 0;
    double lastFrame = 0;

    Direction nextDirection = Direction::NONE;

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    EntityManager entityManager;
    RenderSystem *renderSystem = nullptr;
    MovementSystem *movementSystem = nullptr;
    CollisionSystem *collisionSystem = nullptr;

    std::shared_ptr<Entity> snake;
    std::shared_ptr<Entity> food;

    void generateFood();

public:
    ~Game();

    bool init();
    void run();
    void handleEvents();
    void update();
    void render() const;
    void clean() const;
};
