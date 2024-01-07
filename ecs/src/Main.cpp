#include <SFML/Graphics.hpp>
#include <iostream>
#include "Registry.hpp"
#include "SparseArray.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"
#include "Components/Drawable.hpp"
#include "Components/Controllable.hpp"
#include "Systems.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "ECS");
    GameEngine::Registry registry(1024);

    window.setFramerateLimit(60);

    registry.registerComponent<GameEngine::Controllable>();
    registry.registerComponent<GameEngine::Drawable>();
    registry.registerComponent<GameEngine::Position>();
    registry.registerComponent<GameEngine::Velocity>();

    GameEngine::Entity movableEntity = registry.spawnEntity();
    registry.addComponent<GameEngine::Controllable>(movableEntity, GameEngine::Controllable{});
    registry.addComponent<GameEngine::Drawable>(movableEntity, GameEngine::Drawable{});
    registry.addComponent<GameEngine::Position>(movableEntity, GameEngine::Position{});
    registry.addComponent<GameEngine::Velocity>(movableEntity, GameEngine::Velocity{});

    for (int i = 0; i < 5; ++i) {
        GameEngine::Entity staticEntity = registry.spawnEntity();
        registry.addComponent<GameEngine::Drawable>(staticEntity, GameEngine::Drawable{});
        registry.addComponent<GameEngine::Position>(staticEntity, GameEngine::Position{});
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Example usage of the position_system
        GameEngine::System system;
        system.positionSystem(registry);

        // Example usage of the control_system
        system.controlSystem(registry);

        // Example usage of the draw_system
        system.drawSystem(registry);

        // Clear the window
        window.clear();

        // Render your entities using SFML

        // ...

        // Display the rendered entities
        window.display();
    }

    return 0;
}
