#include "Registry.hpp"
#include "Entity.hpp"
#include "Components/Controllable.hpp"
#include "Components/Drawable.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"
#include "Systems.hpp"
#include <iostream>

int main()
{
    std::cout << "Hello, World!" << std::endl;
    GameEngine::Registry registry(1024);
    std::cout << "Registry created" << std::endl;

    registry.registerComponent<GameEngine::Position>();
    std::cout << "Position component registered" << std::endl;
    registry.registerComponent<GameEngine::Velocity>();
    std::cout << "Velocity component registered" << std::endl;
    registry.registerComponent<GameEngine::Drawable>();
    std::cout << "Drawable component registered" << std::endl;
    registry.registerComponent<GameEngine::Controllable>();
    std::cout << "Controllable component registered" << std::endl;

    // Create a movable entity with all components
    std::cout << "Creating movable entity" << std::endl;
    GameEngine::Entity movableEntity = registry.spawnEntity();
    std::cout << "Movable entity created" << std::endl;
    registry.addComponent<GameEngine::Controllable>(movableEntity, GameEngine::Controllable{true});
    std::cout << "Controllable component added" << std::endl;
    registry.addComponent<GameEngine::Drawable>(movableEntity, GameEngine::Drawable{});
    std::cout << "Drawable component added" << std::endl;
    registry.addComponent<GameEngine::Position>(movableEntity, GameEngine::Position{});
    std::cout << "Position component added" << std::endl;
    registry.addComponent<GameEngine::Velocity>(movableEntity, GameEngine::Velocity{});
    std::cout << "Velocity component added" << std::endl;

    // Create static entities with Drawable and Position components
    for (int i = 0; i < 5; ++i) {
        GameEngine::Entity staticEntity = registry.spawnEntity();
        registry.addComponent<GameEngine::Drawable>(staticEntity, GameEngine::Drawable{});
        registry.addComponent<GameEngine::Position>(staticEntity, GameEngine::Position{});
    }

    return 0;
}
