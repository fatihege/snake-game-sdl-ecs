#include "Game.h"

#include <iostream>
#include <SDL.h>

#include "components/FoodComponent.h"
#include "components/RenderComponent.h"
#include "components/SnakeComponent.h"
#include "components/TransformComponent.h"
#include "core/Utility.h"

void Game::generateFood() {
    const bool special = Utility::random(1, 10) == 1;
    float specialTimer = 0.0f;

    if (special) {
        specialTimer = Utility::random(2.0f, 5.0f);
        std::cout << "Special timer: " << specialTimer << '\n';
    }

    food = entityManager.createEntity();
    food->addComponent<TransformComponent>(Utility::random(0, GRID_WIDTH - 1), Utility::random(0, GRID_HEIGHT - 1),
                                           CELL_HEIGHT, CELL_HEIGHT);
    food->addComponent<RenderComponent>(special ? SDL_Color{214, 99, 255, 255} : SDL_Color{255, 74, 74, 255});
    food->addComponent<FoodComponent>(special, specialTimer);
}

Game::~Game() {
    clean();
}

bool Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL Initialization Failed: " << SDL_GetError() << '\n';
        return false;
    }

    window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GRID_WIDTH * CELL_WIDTH,
                              GRID_HEIGHT * CELL_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window Creation Failed: " << SDL_GetError() << '\n';
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer Creation Failed: " << SDL_GetError() << '\n';
        return false;
    }

    renderSystem = new RenderSystem(renderer);
    movementSystem = new MovementSystem();
    collisionSystem = new CollisionSystem();

    movementSystem->onCollision = [this] {
        this->running = false;
    };

    snake = entityManager.createEntity();
    snake->addComponent<TransformComponent>(Utility::random(0, GRID_WIDTH - 1), Utility::random(0, GRID_HEIGHT - 1),
                                            CELL_HEIGHT, CELL_HEIGHT);
    snake->addComponent<RenderComponent>(SDL_Color{255, 255, 255, 255});
    snake->addComponent<SnakeComponent>();

    generateFood();

    renderSystem->addEntity(snake);
    renderSystem->addEntity(food);
    movementSystem->addEntity(snake);
    collisionSystem->addEntity(snake);
    collisionSystem->addEntity(food);

    running = true;
    return true;
}

void Game::run() {
    while (running) {
        dt = (SDL_GetTicks() - lastFrame) / 1000.0;
        handleEvents();
        update();
        render();
        lastFrame = SDL_GetTicks();
        SDL_Delay(100);
    }
}

void Game::handleEvents() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) running = false;
        else if (event.type == SDL_KEYDOWN) {
            Direction newDirection = Direction::NONE;

            switch (event.key.keysym.sym) {
                case SDLK_w:
                case SDLK_UP:
                    newDirection = Direction::UP;
                    break;
                case SDLK_a:
                case SDLK_LEFT:
                    newDirection = Direction::LEFT;
                    break;
                case SDLK_s:
                case SDLK_DOWN:
                    newDirection = Direction::DOWN;
                    break;
                case SDLK_d:
                case SDLK_RIGHT:
                    newDirection = Direction::RIGHT;
                    break;
                case SDLK_ESCAPE:
                    running = false;
                    break;
                default: break;
            }

            if (newDirection != Direction::NONE) {
                Direction currentDirection;
                if (!inputQueue.empty()) currentDirection = inputQueue.back();
                else currentDirection = snake->getComponent<SnakeComponent>()->direction;

                const bool valid = !(
                    (currentDirection == Direction::UP && newDirection == Direction::DOWN) ||
                    (currentDirection == Direction::DOWN && newDirection == Direction::UP) ||
                    (currentDirection == Direction::LEFT && newDirection == Direction::RIGHT) ||
                    (currentDirection == Direction::RIGHT && newDirection == Direction::LEFT)
                );

                if (valid) inputQueue.push(newDirection);
            }
        }
    }
}

void Game::update() {
    if (!inputQueue.empty()) {
        snake->getComponent<SnakeComponent>()->direction = inputQueue.front();
        inputQueue.pop();
    }

    movementSystem->update();
    collisionSystem->update();

    if (food->isActive()) {
        if (const auto foodComponent = food->getComponent<FoodComponent>(); foodComponent && foodComponent->special) {
            foodComponent->timer -= dt;
            if (foodComponent->timer <= 0.0f) food->destroy();
        }
    }

    if (!food->isActive()) {
        renderSystem->removeEntity(food);
        collisionSystem->removeEntity(food);
        generateFood();
        renderSystem->addEntity(food);
        collisionSystem->addEntity(food);
    }

    entityManager.removeInactiveEntities();
}

void Game::render() const {
    SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
    SDL_RenderClear(renderer);

    renderSystem->update();

    SDL_RenderPresent(renderer);
}

void Game::clean() const {
    delete renderSystem;
    delete movementSystem;
    delete collisionSystem;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
