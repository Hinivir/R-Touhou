/*
** EPITECH PROJECT, 2024
** R-Touhou
** File description:
** Game
*/

#include "Server.hpp"
#include "Init.hpp"

void initGame()
{
    GameEngine::Registry registry(2048);
    std::vector<GameEngine::Entity> entityVector;

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

    GameEngine::Entity background = createBackgroundStar(registry);
    entityVector.push_back(background);
    for (int i = 1; i <= PLAYER_NUMBER; i++) {
        GameEngine::Entity player = spawnMovableEntity(registry);
        registry.getComponent<GameEngine::Position>()[player].value().y = 100 + i * 100;
        entityVector.push_back(player);
    }

    for (int i = 0; i < std::rand() % 31; ++i) {
        GameEngine::Entity staticEntity = spawnEnemyEntity(registry);
        entityVector.push_back(staticEntity);
    }

    // need to init enemies

    GameEngine::Entity groundDown = createGroundDown(registry);
    entityVector.push_back(groundDown);
    GameEngine::Entity groundUp = createGroundUp(registry);
    entityVector.push_back(groundUp);
    GameEngine::Entity score = createScore(registry);
    entityVector.push_back(score);
    GameEngine::Entity gameOver = createGameOver(registry);
    entityVector.push_back(gameOver);
    GameEngine::Entity youWin = createYouWin(registry);
    entityVector.push_back(youWin);

    // need to create a map of enemies
    // need to init background but draw == false
    // need to init walls but draw == false
    // don't need to draw
    std::cout << "Game initialized" << std::endl;
}
