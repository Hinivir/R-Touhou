/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Game.cpp
*/

#include "../include/Client.hpp"
#include "Registry.hpp"
#include "Systems.hpp"
#include "Macros/ForEach.hpp"
#include "Components/Window.hpp"

#define REGISTER_COMPONENT(COMPONENT) registry.registerComponent<COMPONENT>();

GameEngine::Entity spawnBaseEntity(GameEngine::Registry &registry)
{
    GameEngine::Entity entity = registry.spawnEntity();

    registry.addComponent<GameEngine::Drawable>(entity, GameEngine::Drawable{true});
    return entity;
}

GameEngine::Entity spawnMovableEntity(GameEngine::Registry &registry)
{
    GameEngine::Entity entity = spawnBaseEntity(registry);

    registry.addComponent<GameEngine::Controllable>(entity, GameEngine::Controllable{true});
    registry.addComponent<GameEngine::Position>(entity, GameEngine::Position{0.0f, 500.0f});
    registry.addComponent<GameEngine::Velocity>(entity, GameEngine::Velocity{10.0f, 10.0f});
    registry.addComponent<GameEngine::Size>(entity, GameEngine::Size{50.0f, 50.0f});
    registry.addComponent<GameEngine::Sprite>(entity, GameEngine::Sprite{"../games/resources/R-Touhou/graphics/Player.png",sf::Sprite(),sf::Texture()});
    registry.addComponent<GameEngine::Life>(entity, GameEngine::Life{3});
    registry.addComponent<GameEngine::Hitbox>(entity, GameEngine::Hitbox{});
    return entity;
}

GameEngine::Entity spawnEnemyEntity(GameEngine::Registry &registry)
{
    GameEngine::Entity entity = spawnBaseEntity(registry);

    registry.addComponent<GameEngine::Size>(entity, GameEngine::Size{50.0f, 50.0f});
    registry.addComponent<GameEngine::Position>(entity, GameEngine::Position{30.0f, 30.0f});
    registry.addComponent<GameEngine::Velocity>(entity, GameEngine::Velocity{15.5f, 0.0f});
    registry.addComponent<GameEngine::Sprite>(entity, GameEngine::Sprite{"../games/resources/R-Touhou/graphics/Enemy.png",sf::Sprite(),sf::Texture()});
    registry.addComponent<GameEngine::Hitbox>(entity, GameEngine::Hitbox{});
    registry.addComponent<GameEngine::Path>(entity, GameEngine::Path{30.0f, 30.0f, 0.0f, 0.0f});
    registry.addComponent<GameEngine::Life>(entity, GameEngine::Life{2});
    registry.addComponent<GameEngine::Controllable>(entity, GameEngine::Controllable{false});
    return entity;
}

GameEngine::Entity createBackgroundStar(GameEngine::Registry &registry)
{
    GameEngine::Entity backgroundStar = registry.spawnEntity();

    registry.addComponent<GameEngine::Drawable>(backgroundStar, GameEngine::Drawable{true});
    registry.addComponent<GameEngine::Size>(backgroundStar, GameEngine::Size{WINDOW_WIDTH, WINDOW_HEIGHT});
    registry.addComponent<GameEngine::Position>(backgroundStar, GameEngine::Position{0.0f, 0.0f});
    registry.addComponent<GameEngine::Velocity>(backgroundStar, GameEngine::Velocity{10.0f, 0.0f});
    registry.addComponent<GameEngine::Sprite>(backgroundStar, GameEngine::Sprite{"../games/resources/R-Touhou/graphics/BackgroundStar.jpg",sf::Sprite(),sf::Texture()});
    registry.addComponent<GameEngine::ZIndex>(backgroundStar, GameEngine::ZIndex{GAME_ENGINE_Z_INDEX_VALUE_LOWEST_VALUE});

    return backgroundStar;
}

GameEngine::Entity createGroundDown(GameEngine::Registry &registry)
{
    GameEngine::Entity groundDown = registry.spawnEntity();

    registry.addComponent<GameEngine::Drawable>(groundDown, GameEngine::Drawable{true});
    registry.addComponent<GameEngine::Size>(groundDown, GameEngine::Size{1920.0f, 50.0f});
    registry.addComponent<GameEngine::Position>(groundDown, GameEngine::Position{0.0f, 0.0f});
    registry.addComponent<GameEngine::Sprite>(groundDown, GameEngine::Sprite{"../games/resources/R-Touhou/graphics/Ground.png",sf::Sprite(),sf::Texture()});
    registry.addComponent<GameEngine::ZIndex>(groundDown, GameEngine::ZIndex{GAME_ENGINE_Z_INDEX_VALUE_LOWEST_VALUE + 1});
    registry.addComponent<GameEngine::Controllable>(groundDown, GameEngine::Controllable{false});

    return groundDown;
}

GameEngine::Entity createGroundUp(GameEngine::Registry &registry)
{
    GameEngine::Entity groundUp = registry.spawnEntity();

    registry.addComponent<GameEngine::Drawable>(groundUp, GameEngine::Drawable{true});
    registry.addComponent<GameEngine::Size>(groundUp, GameEngine::Size{1920.0f, 50.0f});
    registry.addComponent<GameEngine::Position>(groundUp, GameEngine::Position{0.0f, 1030.0f});
    registry.addComponent<GameEngine::Sprite>(groundUp, GameEngine::Sprite{"../games/resources/R-Touhou/graphics/Ground.png",sf::Sprite(),sf::Texture()});
    registry.addComponent<GameEngine::ZIndex>(groundUp, GameEngine::ZIndex{GAME_ENGINE_Z_INDEX_VALUE_LOWEST_VALUE + 2});
    registry.addComponent<GameEngine::Controllable>(groundUp, GameEngine::Controllable{false});

    return groundUp;
}

GameEngine::Entity createScore(GameEngine::Registry &registry)
{
    GameEngine::Entity score = registry.spawnEntity();

    registry.addComponent<GameEngine::Drawable>(score, GameEngine::Drawable{true});
    registry.addComponent<GameEngine::Position>(score, GameEngine::Position{0.0f, 0.0f});
    registry.addComponent<GameEngine::ZIndex>(score, GameEngine::ZIndex{GAME_ENGINE_Z_INDEX_VALUE_DEFAULT_VALUE});
    registry.addComponent<GameEngine::Color>(score, GameEngine::Color{255, 255, 255, 255});
    std::string scoreText = "Score: 0";
    registry.addComponent<GameEngine::Text>(score, GameEngine::Text{sf::Text(), sf::Font(), scoreText, "../games/resources/R-Touhou/font/arial.ttf", 40});


    return score;
}

GameEngine::Entity createGameOver(GameEngine::Registry &registry)
{
    GameEngine::Entity gameOver = registry.spawnEntity();

    registry.addComponent<GameEngine::Drawable>(gameOver, GameEngine::Drawable{false});
    registry.addComponent<GameEngine::Position>(gameOver, GameEngine::Position{WINDOW_WIDTH / 2 - 220, WINDOW_HEIGHT / 2 - 120});
    registry.addComponent<GameEngine::ZIndex>(gameOver, GameEngine::ZIndex{GAME_ENGINE_Z_INDEX_VALUE_DEFAULT_VALUE});
    registry.addComponent<GameEngine::Color>(gameOver, GameEngine::Color{255, 255, 255, 255});
    std::string gameOverText = "Game Over";
    registry.addComponent<GameEngine::Text>(gameOver, GameEngine::Text{sf::Text(), sf::Font(), gameOverText, "../games/resources/R-Touhou/font/arial.ttf", 80});

    return gameOver;
}

GameEngine::Entity createYouWin(GameEngine::Registry &registry)
{
    GameEngine::Entity youWin = registry.spawnEntity();

    registry.addComponent<GameEngine::Drawable>(youWin, GameEngine::Drawable{false});
    registry.addComponent<GameEngine::Position>(youWin, GameEngine::Position{WINDOW_WIDTH / 2 - 220, WINDOW_HEIGHT / 2 - 120});
    registry.addComponent<GameEngine::ZIndex>(youWin, GameEngine::ZIndex{GAME_ENGINE_Z_INDEX_VALUE_DEFAULT_VALUE});
    registry.addComponent<GameEngine::Color>(youWin, GameEngine::Color{255, 255, 255, 255});
    std::string youWinText = "You Win !";
    registry.addComponent<GameEngine::Text>(youWin, GameEngine::Text{sf::Text(), sf::Font(), youWinText, "../games/resources/R-Touhou/font/arial.ttf", 80});

    return youWin;
}

void Client::runGame(std::string const gamename)
{
    int nbRegistry = 1024;
    int testscore = 0;
    bool isGameOver = false;
    startInit = true;

//    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), gamename);
    GameEngine::Registry registry(nbRegistry);
    GameEngine::System system;

//    window.setFramerateLimit(60);

    GAME_ENGINE_FOR_EACH(REGISTER_COMPONENT
        ,GameEngine::Color
        ,GameEngine::Controllable
        ,GameEngine::Drawable
        ,GameEngine::Hitbox
        ,GameEngine::Life
        ,GameEngine::Path
        ,GameEngine::Position
        ,GameEngine::Projectile
        ,GameEngine::Size
        ,GameEngine::Sprite
        ,GameEngine::SpriteTextureAnimation
        ,GameEngine::SpriteTextureRect
        ,GameEngine::Text
        ,GameEngine::Velocity
        ,GameEngine::ZIndex
    )

    GameEngine::Entity movableEntity = spawnMovableEntity(registry);
    GameEngine::Entity backgroundStar = createBackgroundStar(registry);
    GameEngine::Entity groundDown = createGroundDown(registry);
    GameEngine::Entity groundUp = createGroundUp(registry);
    GameEngine::Entity score = createScore(registry);
    GameEngine::Entity gameOver = createGameOver(registry);
    GameEngine::Entity youWin = createYouWin(registry);
    std::vector<GameEngine::Entity> entityVector = {};

    while (!hasEnemy) { }

    std::cout << "enemies size: " << enemies.size() << std::endl;

    for (std::size_t i = 0; i < enemies.size(); i++)
        entityVector.push_back(enemies[i]);

    std::cout << "enneies size: " << enemies.size() << std::endl;
    std::cout << "entity size: " << entityVector.size() << std::endl;
    std::cout << "x = " << registry.getComponent<GameEngine::Position>()[entityVector[0]].value().x << std::endl;
    posNb = entityVector.size();

    while (allPos.size() != posNb) {
    }
    //receive

//    system.initEnemy(registry);
    /*
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
            window.close();
        registry.getComponent<GameEngine::Text>()[score].value().string = ("Score: " + std::to_string(testscore));

        system.backgroundParallax(registry);
        system.controlSystem(registry);
        system.spriteSystem(registry);
        system.attackSystem(registry);
        system.drawSystem(registry, window);
        system.deleteEntitiesSystem(registry);
        window.display();
        window.clear();
        if (testscore == 100) {
            for (const auto& entity : entityVector)
                registry.garbageEntities.push_back(entity);
            registry.garbageEntities.push_back(movableEntity);
            registry.garbageEntities.push_back(backgroundStar);
            registry.garbageEntities.push_back(groundDown);
            registry.garbageEntities.push_back(groundUp);
            window.clear(sf::Color::Black);
            registry.getComponent<GameEngine::Drawable>()[youWin].value().isVisible = true;
        }
        if (!isGameOver && registry.getComponent<GameEngine::Life>()[movableEntity].value().life <= 0) {
            for (const auto &entity : entityVector)
                registry.garbageEntities.push_back(entity);
            registry.garbageEntities.push_back(movableEntity);
            registry.garbageEntities.push_back(backgroundStar);
            registry.garbageEntities.push_back(groundDown);
            registry.garbageEntities.push_back(groundUp);
            window.clear(sf::Color::Black);
            registry.getComponent<GameEngine::Drawable>()[gameOver].value().isVisible = true;
            isGameOver = true;
        }
    }
    */
}
