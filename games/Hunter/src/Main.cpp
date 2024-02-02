/*
** EPITECH PROJECT, 2024
** R-Touhou
** File description:
** Main
*/

#include "Registry.hpp"
#include "Systems.hpp"
#include "Systems/Draw.hpp"
#include "Systems/Sprite.hpp"

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

GameEngine::Entity spawnBaseEntity(GameEngine::Registry &registry)
{
    GameEngine::Entity entity = registry.spawnEntity();

    registry.addComponent<GameEngine::Drawable>(entity, GameEngine::Drawable{true});
    registry.addComponent<GameEngine::Outline>(entity, GameEngine::Outline{5});
    return entity;
}

GameEngine::Entity createGameOver(GameEngine::Registry &registry)
{
    GameEngine::Entity gameOver = registry.spawnEntity();

    registry.addComponent<GameEngine::Drawable>(gameOver, GameEngine::Drawable{false});
    registry.addComponent<GameEngine::Position>(
        gameOver, GameEngine::Position{800 / 2 - 160, 600 / 2 - 10});
    registry.addComponent<GameEngine::ZIndex>(gameOver, GameEngine::ZIndex{GAME_ENGINE_Z_INDEX_VALUE_DEFAULT_VALUE});
    registry.addComponent<GameEngine::Color>(gameOver, GameEngine::Color{255, 255, 255, 255});
    std::string gameOverText = "Game Over";
    registry.addComponent<GameEngine::Text>(
        gameOver, GameEngine::Text{sf::Text(), sf::Font(), gameOverText, "../resources/R-Touhou/font/arial.ttf", 80});

    return gameOver;
}

GameEngine::Entity createYouWin(GameEngine::Registry &registry)
{
    GameEngine::Entity youWin = registry.spawnEntity();

    registry.addComponent<GameEngine::Drawable>(youWin, GameEngine::Drawable{false});
    registry.addComponent<GameEngine::Position>(
        youWin, GameEngine::Position{800 / 2 - 160, 600 / 2 - 10});
    registry.addComponent<GameEngine::ZIndex>(youWin, GameEngine::ZIndex{GAME_ENGINE_Z_INDEX_VALUE_DEFAULT_VALUE});
    registry.addComponent<GameEngine::Color>(youWin, GameEngine::Color{255, 255, 255, 255});
    std::string youWinText = "You Win !";
    registry.addComponent<GameEngine::Text>(
        youWin, GameEngine::Text{sf::Text(), sf::Font(), youWinText, "../resources/R-Touhou/font/arial.ttf", 80});

    return youWin;
}

std::pair<float, float> getRandomVelocity()
{
    int random = rand() % 8 + 1;
    float velocityX = 0.0f;
    float velocityY = 0.0f;

    switch (random) {
        case 1:
            velocityX = 5.0f;
            velocityY = 5.0f;
            break;
        case 2:
            velocityX = -5.0f;
            velocityY = 5.0f;
            break;
        case 3:
            velocityX = 5.0f;
            velocityY = -5.0f;
            break;
        case 4:
            velocityX = -5.0f;
            velocityY = -5.0f;
            break;
        case 5:
            velocityX = 5.0f;
            velocityY = 0.0f;
            break;
        case 6:
            velocityX = -5.0f;
            velocityY = 0.0f;
            break;
        case 7:
            velocityX = 0.0f;
            velocityY = 5.0f;
            break;
        case 8:
            velocityX = 0.0f;
            velocityY = -5.0f;
            break;
    }
    return std::make_pair(velocityX, velocityY);
}

GameEngine::Entity createDuck(GameEngine::Registry &registry)
{
    srand(static_cast<unsigned>(time(0)));
    GameEngine::Entity duck = spawnBaseEntity(registry);
    registry.addComponent<GameEngine::Sprite>(duck, GameEngine::Sprite{"../resources/R-Touhou/graphics/Fish.png", sf::Sprite(), sf::Texture()});
    float x = static_cast<float>(rand() % 700);
    float y = static_cast<float>(rand() % 500);
    registry.addComponent<GameEngine::Position>(duck, GameEngine::Position{x, y});
    registry.addComponent<GameEngine::Size>(duck, GameEngine::Size{50.0f, 50.0f});
    std::pair<float, float> velocity = getRandomVelocity();
    registry.addComponent<GameEngine::Velocity>(duck, GameEngine::Velocity{velocity.first, velocity.second});
    registry.addComponent<GameEngine::Drawable>(duck, GameEngine::Drawable{true});
    registry.addComponent<GameEngine::Path>(duck, GameEngine::Path{x, y, 800, 600});

    return duck;
}

GameEngine::Entity createBackground(GameEngine::Registry &registry)
{
    GameEngine::Entity background = registry.spawnEntity();
    registry.addComponent<GameEngine::Sprite>(background, GameEngine::Sprite{"../resources/R-Touhou/graphics/Background.jpg", sf::Sprite(), sf::Texture()});
    registry.addComponent<GameEngine::Position>(background, GameEngine::Position{0.0f, 0.0f});
    registry.addComponent<GameEngine::Size>(background, GameEngine::Size{800.0f, 600.0f});
    registry.addComponent<GameEngine::Drawable>(background, GameEngine::Drawable{true});
    registry.addComponent<GameEngine::ZIndex>(background, GameEngine::ZIndex{GAME_ENGINE_Z_INDEX_VALUE_LOWEST_VALUE});
    return background;
}

GameEngine::Entity createScore(GameEngine::Registry &registry)
{
    GameEngine::Entity score = registry.spawnEntity();

    registry.addComponent<GameEngine::Drawable>(score, GameEngine::Drawable{true});
    registry.addComponent<GameEngine::Position>(score, GameEngine::Position{10.0f, 10.0f});
    registry.addComponent<GameEngine::ZIndex>(score, GameEngine::ZIndex{GAME_ENGINE_Z_INDEX_VALUE_DEFAULT_VALUE});
    registry.addComponent<GameEngine::Color>(score, GameEngine::Color{255, 255, 255, 255});
    std::string scoreText = "Score: 0";
    registry.addComponent<GameEngine::Text>(
        score, GameEngine::Text{sf::Text(), sf::Font(), scoreText, "../resources/R-Touhou/font/arial.ttf", 24});

    return score;
}

int main()
{
    int score = 0;
    //bool isGameOver = false;
    srand(static_cast<unsigned>(time(0)));
    std::vector<GameEngine::Entity> entityVector;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Duck Hunt");
    GameEngine::Registry registry(2048);
    GameEngine::SystemGroup system;

    window.setFramerateLimit(60);

    registry.registerComponent<GameEngine::Color>();
    registry.registerComponent<GameEngine::ZIndex>();
    registry.registerComponent<GameEngine::Outline>();
    registry.registerComponent<GameEngine::Sprite>();
    registry.registerComponent<GameEngine::SpriteTextureAnimation>();
    registry.registerComponent<GameEngine::SpriteTextureRect>();

    registry.registerComponent<GameEngine::Hitbox>();
    registry.registerComponent<GameEngine::Life>();
    registry.registerComponent<GameEngine::Path>();

    registry.registerComponent<GameEngine::Controllable>();
    registry.registerComponent<GameEngine::Drawable>();
    registry.registerComponent<GameEngine::Position>();
    registry.registerComponent<GameEngine::Projectile>();
    registry.registerComponent<GameEngine::Size>();
    registry.registerComponent<GameEngine::Text>();
    registry.registerComponent<GameEngine::Velocity>();

    GameEngine::Entity background = createBackground(registry);
    entityVector.push_back(background);
    GameEngine::Entity duck = createDuck(registry);
    entityVector.push_back(duck);
    GameEngine::Entity scoreEntity = createScore(registry);
    GameEngine::Entity gameOver = createGameOver(registry);
    GameEngine::Entity youWin = createYouWin(registry);

    float speed = 0.07f;
    int direction = rand() % 4;

    while (window.isOpen()) {
        srand(static_cast<unsigned>(time(0)));
        sf::Event event;
        while (window.pollEvent(event)) {
            if (score == 10) {
                registry.garbageEntities.push_back(duck);
                registry.garbageEntities.push_back(background);
                window.clear(sf::Color::Black);
                registry.getComponent<GameEngine::Drawable>()[youWin].value().isVisible = true;
            }
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                if (registry.getComponent<GameEngine::Sprite>()[duck].value().sprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
                    score++;
                    registry.getComponent<GameEngine::Position>()[duck].value().x = static_cast<float>(rand() % 600);
                    registry.getComponent<GameEngine::Position>()[duck].value().y = static_cast<float>(rand() % 400);
                    std::pair<float, float> velocity = getRandomVelocity();
                    registry.getComponent<GameEngine::Velocity>()[duck].value().x = velocity.first;
                    registry.getComponent<GameEngine::Velocity>()[duck].value().y = velocity.second;
                    registry.getComponent<GameEngine::Text>()[scoreEntity].value().string = "Score: " + std::to_string(score);
                }
            }
        }
/*
        // Move the duck based on the current direction
        if (direction == 0) {
            duck.move(speed, 0); // Horizontal
        } else if (direction == 1) {
            duck.move(0, speed); // Vertical
        } else if (direction == 2) {
            duck.move(speed, speed); // Diagonal
        } else {
            duck.move(-speed, -speed); // Diagonal
        }
*/
        // If the duck goes off the window, reset its position and change direction
        if (registry.getComponent<GameEngine::Position>()[duck].value().x > 800 || registry.getComponent<GameEngine::Position>()[duck].value().x < 0 ||
            registry.getComponent<GameEngine::Position>()[duck].value().y > 600 || registry.getComponent<GameEngine::Position>()[duck].value().y < 0) {
            registry.getComponent<GameEngine::Position>()[duck].value().x = static_cast<float>(rand() % 600);
            registry.getComponent<GameEngine::Position>()[duck].value().y = static_cast<float>(rand() % 400);
            std::pair<float, float> velocity = getRandomVelocity();
            registry.getComponent<GameEngine::Velocity>()[duck].value().x = velocity.first;
            registry.getComponent<GameEngine::Velocity>()[duck].value().y = velocity.second;
        }

        GameEngine::System::sprite(registry);
        GameEngine::System::draw(registry, window);
        //system.movementSystem(registry);
        window.display();
        window.clear();
    }
    return 0;
}
