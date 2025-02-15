cmake_minimum_required(VERSION 3.30)
project(snake_game_sdl_ecs)

set(CMAKE_CXX_STANDARD 20)

add_executable(snake_game_sdl_ecs src/main.cpp
        src/Game.cpp
        src/Game.h
        src/core/ECS.h
        src/core/EntityManager.cpp
        src/core/EntityManager.h
        src/core/Entity.cpp
        src/core/Entity.h
        src/core/Component.h
        src/core/System.h
        src/components/TransformComponent.h
        src/components/RenderComponent.h
        src/components/SnakeComponent.h
        src/components/FoodComponent.h
        src/systems/RenderSystem.cpp
        src/systems/RenderSystem.h
        src/systems/MovementSystem.cpp
        src/systems/MovementSystem.h
        src/systems/CollisionSystem.cpp
        src/systems/CollisionSystem.h
)
