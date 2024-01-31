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

GameEngine::Entity createDuck(GameEngine::Registry &registry)
{
    srand(static_cast<unsigned>(time(0)));
    GameEngine::Entity duck = spawnBaseEntity(registry);
    registry.addComponent<GameEngine::Sprite>(duck, GameEngine::Sprite{"../resources/R-Touhou/graphics/Fish.png", sf::Sprite(), sf::Texture()});
    registry.addComponent<GameEngine::Position>(duck, GameEngine::Position{static_cast<float>(rand() % 700), static_cast<float>(rand() % 500)});
    registry.addComponent<GameEngine::Size>(duck, GameEngine::Size{50.0f, 50.0f});
    registry.addComponent<GameEngine::Velocity>(duck, GameEngine::Velocity{0.07f, 0.07f});
    registry.addComponent<GameEngine::Drawable>(duck, GameEngine::Drawable{true});
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
    entityVector.push_back(scoreEntity);
    int score = 0;

    float speed = 0.07f;
    int direction = rand() % 4;

    while (window.isOpen()) {
        srand(static_cast<unsigned>(time(0)));
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                if (registry.getComponent<GameEngine::Sprite>()[duck].value().sprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
                    score++;
                    registry.getComponent<GameEngine::Position>()[duck].value().x = static_cast<float>(rand() % 700);
                    registry.getComponent<GameEngine::Position>()[duck].value().y = static_cast<float>(rand() % 500);
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

        // If the duck goes off the window, reset its position and change direction
        if (duck.getPosition().x > window.getSize().x || duck.getPosition().x < 0 ||
            duck.getPosition().y > window.getSize().y || duck.getPosition().y < 0) {
            duck.setPosition(rand() % 790, rand() % 590);
            direction = rand() % 3;
        }
*/
        GameEngine::System::sprite(registry);
        GameEngine::System::draw(registry, window);
        //system.movementSystem(registry);
        window.display();
        window.clear();
    }
    return 0;
}
