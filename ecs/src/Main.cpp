#include <SFML/Graphics.hpp>
#include <iostream>
#include "Registry.hpp"
#include "SparseArray.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"
#include "Components/Drawable.hpp"
#include "Components/Controllable.hpp"
#include "Components/Sprite.hpp"
#include "Components/Color.hpp"
#include "Components/ZIndex.hpp"
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
    registry.registerComponent<GameEngine::Sprite>();
    registry.registerComponent<GameEngine::Color>();
    registry.registerComponent<GameEngine::ZIndex>();

    GameEngine::Entity movableEntity = registry.spawnEntity();
    registry.addComponent<GameEngine::Controllable>(movableEntity, GameEngine::Controllable{true});
    registry.addComponent<GameEngine::Drawable>(movableEntity, GameEngine::Drawable{true});
    registry.addComponent<GameEngine::Position>(movableEntity, GameEngine::Position{0.0f, 0.0f});
    registry.addComponent<GameEngine::Velocity>(movableEntity, GameEngine::Velocity{0.0f, 0.0f});
    registry.addComponent<GameEngine::Sprite>(movableEntity, GameEngine::Sprite{"../resources/R-Touhou/graphics/Fish.png",sf::Sprite(),sf::Texture()});
    registry.addComponent<GameEngine::ZIndex>(movableEntity, GameEngine::ZIndex{GAME_ENGINE_Z_INDEX_VALUE_DEFAULT_VALUE - 1});

    for (int i = 0; i < 5; ++i) {
        GameEngine::Entity staticEntity = registry.spawnEntity();
        registry.addComponent<GameEngine::Drawable>(staticEntity, GameEngine::Drawable{true});
        registry.addComponent<GameEngine::Position>(staticEntity, GameEngine::Position{});
        registry.addComponent<GameEngine::Color>(staticEntity, GameEngine::Color{0, 255, 0, 100});
        registry.addComponent<GameEngine::Sprite>(staticEntity, GameEngine::Sprite{"",sf::Sprite(),sf::Texture()});
        registry.addComponent<GameEngine::ZIndex>(staticEntity, GameEngine::ZIndex{});
    }

    GameEngine::System system;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        system.positionSystem(registry);
        system.controlSystem(registry);

        system.spriteSystem(registry, movableEntity);
        system.drawSystem(registry, window);
        window.display();
        window.clear();
    }

    return 0;
}
