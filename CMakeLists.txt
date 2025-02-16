cmake_minimum_required(VERSION 3.30)
project(snake_game_sdl_ecs)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)

add_executable(snake_game_sdl_ecs src/main.cpp
        src/Game.cpp
        src/Game.h
        src/core/EntityManager.cpp
        src/core/EntityManager.h
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
        src/core/Utility.cpp
        src/core/Utility.h
)

target_link_libraries(snake_game_sdl_ecs
        PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)
target_link_libraries(snake_game_sdl_ecs PRIVATE $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>)
target_link_libraries(snake_game_sdl_ecs PRIVATE $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>)
