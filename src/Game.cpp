#include "Game.h"

#include <iostream>
#include <SDL.h>

#include "components/FoodComponent.h"
#include "components/RenderComponent.h"
#include "components/SnakeComponent.h"
#include "components/TransformComponent.h"

void Game::generateFood() {
    food = entityManager.createEntity();
    food->addComponent<TransformComponent>(rand() % GRID_WIDTH, rand() % GRID_HEIGHT, CELL_HEIGHT, CELL_HEIGHT);
    food->addComponent<RenderComponent>(SDL_Color{255, 0, 0, 255});
    food->addComponent<FoodComponent>();
}

Game::~Game() {
    clean();
}

bool Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL Initialization Failed: " << SDL_GetError() << '\n';
        return false;
    }

    window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
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

    snake = entityManager.createEntity();
    snake->addComponent<TransformComponent>(rand() % GRID_WIDTH, rand() % GRID_HEIGHT, CELL_HEIGHT, CELL_HEIGHT);
    snake->addComponent<RenderComponent>(SDL_Color{0, 0, 0, 255});
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
            switch (event.key.keysym.sym) {
                case SDLK_w:
                case SDLK_UP:
                    snake->getComponent<SnakeComponent>()->direction = Direction::UP;
                    break;
                case SDLK_a:
                case SDLK_LEFT:
                    snake->getComponent<SnakeComponent>()->direction = Direction::LEFT;
                    break;
                case SDLK_s:
                case SDLK_DOWN:
                    snake->getComponent<SnakeComponent>()->direction = Direction::DOWN;
                    break;
                case SDLK_d:
                case SDLK_RIGHT:
                    snake->getComponent<SnakeComponent>()->direction = Direction::RIGHT;
                    break;
                case SDLK_ESCAPE:
                    running = false;
                    break;
                default: ;
            }
        }
    }
}

void Game::update() {
    movementSystem->update();
    collisionSystem->update();

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
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
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
