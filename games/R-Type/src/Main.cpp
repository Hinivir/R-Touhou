/*
** EPITECH PROJECT, 2024
** R-Touhou_Bootstrap
** File description:
** Main.cpp
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Registry.hpp"
#include "Systems.hpp"
#include "Macros/ForEach.hpp"
#include "Init.hpp"

#define REGISTER_COMPONENT(COMPONENT) registry.registerComponent<COMPONENT>();

bool restartGame(GameEngine::Registry &registry, sf::RenderWindow &window, bool &isGameOver)
{
    registry.clear();
    isGameOver = false;
    return isGameOver;
}

int main()
{
    int nbRegistry = 2048;
    int totalScore = 0;
    bool isGameOver = false;
    int shootCoolDown = 0;
    int enemyCoolDown = 0;
    bool spawnEnemy = true;
    std::vector<GameEngine::Entity> entityVector;

    // client
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "R-Touhou");
    GameEngine::Registry registry(nbRegistry);
    GameEngine::System system;

    window.setFramerateLimit(60);

    // both
    /*GAME_ENGINE_FOR_EACH(REGISTER_COMPONENT, GameEngine::Color, GameEngine::Controllable, GameEngine::Drawable,
        GameEngine::Hitbox, GameEngine::Life, GameEngine::Path, GameEngine::Position, GameEngine::Projectile,
        GameEngine::Size, GameEngine::Sprite, GameEngine::SpriteTextureAnimation, GameEngine::SpriteTextureRect,
        GameEngine::Text, GameEngine::Velocity, GameEngine::ZIndex)*/

    registry.registerComponent<GameEngine::Color>();//c
    registry.registerComponent<GameEngine::ZIndex>();//c
    registry.registerComponent<GameEngine::Outline>();//c
    registry.registerComponent<GameEngine::Sprite>();//c
    registry.registerComponent<GameEngine::SpriteTextureAnimation>();//c
    registry.registerComponent<GameEngine::SpriteTextureRect>();//c

    registry.registerComponent<GameEngine::Hitbox>();//s
    registry.registerComponent<GameEngine::Life>();//s
    registry.registerComponent<GameEngine::Path>();//s

    registry.registerComponent<GameEngine::Controllable>();//sc
    registry.registerComponent<GameEngine::Drawable>();//sc
    registry.registerComponent<GameEngine::Position>();//sc
    registry.registerComponent<GameEngine::Projectile>();//sc
    registry.registerComponent<GameEngine::Size>();//sc
    registry.registerComponent<GameEngine::Text>();//sc
    registry.registerComponent<GameEngine::Velocity>();//sc

    GameEngine::Entity movableEntity = spawnMovableEntity(registry);
    entityVector.push_back(movableEntity);
    GameEngine::Entity backgroundStar1 = createBackgroundStar(registry);
    entityVector.push_back(backgroundStar1);
    GameEngine::Entity backgroundStar2 = createBackgroundStar(registry);
    registry.getComponent<GameEngine::Position>()[backgroundStar2].value().x = 1920;
    entityVector.push_back(backgroundStar2);
    GameEngine::Entity groundDown = createGroundDown(registry);
    entityVector.push_back(groundDown);
    GameEngine::Entity groundUp = createGroundUp(registry);
    entityVector.push_back(groundUp);
    GameEngine::Entity score = createScore(registry);
    GameEngine::Entity gameOver = createGameOver(registry);
    GameEngine::Entity youWin = createYouWin(registry);

    for (int i = 0; i < std::rand() % 31; ++i) {
        GameEngine::Entity staticEntity = spawnEnemyEntity(registry);
        entityVector.push_back(staticEntity);
    }

    system.initEnemy(registry);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
            window.close();
        registry.getComponent<GameEngine::Text>()[score].value().string = ("Score: " + std::to_string(totalScore));
        system.controlSystem(registry);

        if (shootCoolDown == 7) {
            system.attackSystem(registry, entityVector);
            shootCoolDown = 0;
        }
        if (enemyCoolDown == 50 && spawnEnemy) {
            for (int i = 0; i < std::rand() % 31; ++i) {
                GameEngine::Entity staticEntity = spawnEnemyEntity(registry);
                entityVector.push_back(staticEntity);
            }
            enemyCoolDown = 0;
            system.initEnemy(registry);
        }
        enemyCoolDown++;
        shootCoolDown++;
        system.spriteSystem(registry);
        system.drawSystem(registry, window);
        system.movementSystem(registry);
        system.collisionSystem(registry, totalScore);
        system.deleteEntitiesSystem(registry);
        window.display();
        window.clear();

        if (totalScore == 100) {
            enemyCoolDown = 0;
            spawnEnemy = false;
            for (const auto &entity : entityVector)
                registry.garbageEntities.push_back(entity);
            registry.garbageEntities.push_back(movableEntity);
            registry.garbageEntities.push_back(backgroundStar1);
            registry.garbageEntities.push_back(backgroundStar2);
            registry.garbageEntities.push_back(groundDown);
            registry.garbageEntities.push_back(groundUp);
            window.clear(sf::Color::Black);
            registry.getComponent<GameEngine::Drawable>()[youWin].value().isVisible = true;
        }
        if (!isGameOver && registry.getComponent<GameEngine::Life>()[movableEntity].value().life <= 0) {
            enemyCoolDown = 0;
            spawnEnemy = false;
            for (const auto &entity : entityVector)
                registry.garbageEntities.push_back(entity);
            registry.garbageEntities.push_back(movableEntity);
            registry.garbageEntities.push_back(backgroundStar1);
            registry.garbageEntities.push_back(backgroundStar2);
            registry.garbageEntities.push_back(groundDown);
            registry.garbageEntities.push_back(groundUp);
            window.clear(sf::Color::Black);
            registry.getComponent<GameEngine::Drawable>()[gameOver].value().isVisible = true;
            isGameOver = true;
        }
    }
    return 0;
}
