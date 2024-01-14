/*
** EPITECH PROJECT, 2024
** R-Touhou
** File description:
** Zelda.cpp
*/

#include <iostream>

#include <SFML/Graphics.hpp>

#include "Registry.hpp"
#include "Systems.hpp"

GameEngine::Entity spawnEntity(GameEngine::Registry &registry)
{
    GameEngine::Entity entity = registry.spawnEntity();

    registry.addComponent<GameEngine::Drawable>(entity, GameEngine::Drawable{true});

    return (entity);
}

GameEngine::Entity spawnPlayerZelda(GameEngine::Registry &registry)
{
    GameEngine::Entity zelda = spawnEntity(registry);

    registry.addComponent<GameEngine::Controllable>(zelda, GameEngine::Controllable{true});
    registry.addComponent<GameEngine::Position>(zelda, GameEngine::Position{730.0f, 500.0f});
    registry.addComponent<GameEngine::Velocity>(zelda, GameEngine::Velocity{10.0f, 10.0f});
    registry.addComponent<GameEngine::Size>(zelda, GameEngine::Size{500.0f, 500.0f});
    registry.addComponent<GameEngine::Sprite>(
        zelda, GameEngine::Sprite{"./resources/Zelda/graphics/Zelda.png", sf::Sprite(), sf::Texture()});

    return (zelda);
}

GameEngine::Entity createBackground(GameEngine::Registry &registry)
{
    GameEngine::Entity background = registry.spawnEntity();

    registry.addComponent<GameEngine::Drawable>(background, GameEngine::Drawable{true});
    registry.addComponent<GameEngine::Size>(background, GameEngine::Size{WINDOW_WIDTH, WINDOW_HEIGHT});
    registry.addComponent<GameEngine::Position>(background, GameEngine::Position{0.0f, 0.0f});
    registry.addComponent<GameEngine::Velocity>(background, GameEngine::Velocity{2.0f, 0.0f});
    registry.addComponent<GameEngine::Sprite>(background,
        GameEngine::Sprite{"./resources/Zelda/graphics/BackgroundZelda.jpg", sf::Sprite(), sf::Texture()});
    registry.addComponent<GameEngine::ZIndex>(
        background, GameEngine::ZIndex{GAME_ENGINE_Z_INDEX_VALUE_LOWEST_VALUE});
    registry.addComponent<GameEngine::Color>(background, GameEngine::Color{50, 50, 50});

    return (background);
}

int main(void)
{
    int nbRegistry = 1024;
    bool isGameOver = false;

    std::vector<GameEngine::Entity> entityVector;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SampleGameZelda");
    GameEngine::Registry registry(nbRegistry);
    GameEngine::System system;
    window.setFramerateLimit(60);

    registry.registerComponent<GameEngine::Color>();
    registry.registerComponent<GameEngine::Controllable>();
    registry.registerComponent<GameEngine::Drawable>();
    registry.registerComponent<GameEngine::Hitbox>();
    registry.registerComponent<GameEngine::Life>();
    registry.registerComponent<GameEngine::Outline>();
    registry.registerComponent<GameEngine::Path>();
    registry.registerComponent<GameEngine::Position>();
    registry.registerComponent<GameEngine::Projectile>();
    registry.registerComponent<GameEngine::Size>();
    registry.registerComponent<GameEngine::Sprite>();
    registry.registerComponent<GameEngine::SpriteTextureAnimation>();
    registry.registerComponent<GameEngine::SpriteTextureRect>();
    registry.registerComponent<GameEngine::Text>();
    registry.registerComponent<GameEngine::Velocity>();
    registry.registerComponent<GameEngine::ZIndex>();

    GameEngine::Entity movableEntity = spawnPlayerZelda(registry);
    entityVector.push_back(movableEntity);

    GameEngine::Entity background1 = createBackground(registry);
    entityVector.push_back(background1);

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
            window.close();
        }

        system.controlSystem(registry);
        system.spriteSystem(registry);
        system.drawSystem(registry, window);

        window.display();
        window.clear();
    }
    return (0);
}
