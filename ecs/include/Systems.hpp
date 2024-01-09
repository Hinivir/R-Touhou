/*
** EPITECH PROJECT, 2023
** R-Touhou_Bootstrap
** File description:
** Systems.hpp
*/

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "Registry.hpp"
#include "Components/Color.hpp"
#include "Components/Controllable.hpp"
#include "Components/Drawable.hpp"
#include "Components/Life.hpp"
#include "Components/Position.hpp"
#include "Components/Sprite.hpp"
#include "Components/SpriteTextureRect.hpp"
#include "Components/Velocity.hpp"
#include "Components/ZIndex.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#define DO_COMPONENT_CONTAINS_AT(COMPONENT, ID) (i < COMPONENT.size() && COMPONENT[ID].has_value())

#define EXTRACT_COMPONENT(COMPONENT, VARIABLE) auto &VARIABLE = r.getComponent<COMPONENT>()
#define EXTRACT_COMPONENT_CONST(COMPONENT, VARIABLE) auto const &VARIABLE = r.getComponent<COMPONENT>()

#define FROM_COMPONENT_TO_VARIABLE(COMPONENT, ID, VARIABLE, VARIABLE_HAS) \
    bool const VARIABLE_HAS = DO_COMPONENT_CONTAINS_AT(COMPONENT, ID); auto &VARIABLE = COMPONENT[VARIABLE_HAS ? ID : 0];
#define FROM_COMPONENT_TO_VARIABLE_CONST(COMPONENT, ID, VARIABLE, VARIABLE_HAS) \
    bool const VARIABLE_HAS = DO_COMPONENT_CONTAINS_AT(COMPONENT, ID); auto const &VARIABLE = COMPONENT[VARIABLE_HAS ? ID : 0];

bool isColliding(std::size_t x1, std::size_t y1, std::size_t x2, std::size_t y2, std::size_t width, std::size_t height)
{
    return (x1 < x2 + width && x1 + width > x2 && y1 < y2 + height && y1 + height > y2);
}

namespace GameEngine
{

    class System
    {
      public:
        System() = default;
        ~System() = default;

        void loggingSystem(GameEngine::Registry &r) {
            EXTRACT_COMPONENT_CONST(GameEngine::Position, positions);
            EXTRACT_COMPONENT_CONST(GameEngine::Velocity, velocities);

            for (size_t i = 0; i < positions.size() && i < velocities.size(); ++i) {
                // Position
                FROM_COMPONENT_TO_VARIABLE_CONST(positions, i, positionComponent, hasPosition);
                GameEngine::Position const &position = hasPosition ? positionComponent.value() : GameEngine::Position();
                // Velocity
                FROM_COMPONENT_TO_VARIABLE_CONST(velocities, i, velocityComponent, hasVelocity);
                GameEngine::Velocity const &velocity = hasVelocity ? velocityComponent.value() : GameEngine::Velocity();

                if (hasPosition && hasVelocity) {
                    std ::cerr << i << ": Position = { " << position.pos_x << ", " << position.pos_y
                               << " } , Velocity = { " << velocity.vol_x << ", " << velocity.vol_y << " }"
                               << std ::endl;
                }
            }
        }

        void controlSystem(GameEngine::Registry &r) {
            EXTRACT_COMPONENT_CONST(GameEngine::Controllable, controllables);
            EXTRACT_COMPONENT(GameEngine::Position, positions);
            EXTRACT_COMPONENT_CONST(GameEngine::Velocity, velocities);

            for (size_t i = 0; i < controllables.size() && i < positions.size(); ++i) {
                // Controllable - Continues if controllable is undefined or no controllable
                FROM_COMPONENT_TO_VARIABLE_CONST(controllables, i, controllable, hasControllable);
                if (!hasControllable || !controllable.value().isControllable) continue;
                // Position - Continues if position if undefined
                FROM_COMPONENT_TO_VARIABLE(positions, i, positionComponent, hasPosition);
                if (!hasPosition) continue;
                GameEngine::Position &position = positionComponent.value();
                // Velocity
                FROM_COMPONENT_TO_VARIABLE_CONST(velocities, i, velocityComponent, hasVelocity);
                GameEngine::Velocity const &velocity = hasVelocity ? velocityComponent.value() : GameEngine::Velocity();

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && position.pos_y > -1)
                    position.pos_y -= velocity.vol_y;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && position.pos_y < 1080 - 30)
                    position.pos_y += velocity.vol_y;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && position.pos_x > -1)
                    position.pos_x -= velocity.vol_x;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && position.pos_x < 1920 - 30)
                    position.pos_x += velocity.vol_x;
            }
        }

        void drawSystem(GameEngine::Registry &r, sf::RenderWindow &window) {
            EXTRACT_COMPONENT_CONST(GameEngine::Drawable, drawables);
            EXTRACT_COMPONENT_CONST(GameEngine::Position, positions);
            EXTRACT_COMPONENT(GameEngine::Sprite, sprites);
            EXTRACT_COMPONENT_CONST(GameEngine::Color, colors);
            EXTRACT_COMPONENT_CONST(GameEngine::ZIndex, zIndexes);
            EXTRACT_COMPONENT_CONST(GameEngine::SpriteTextureRect, spriteTextureRects);
            GameEngine::ZIndexValue lowestZIndex = GAME_ENGINE_Z_INDEX_VALUE_LOWEST_VALUE;
            GameEngine::ZIndexValue currentZIndex;

            do {
                currentZIndex = lowestZIndex;
                for (size_t i = 0; i < drawables.size() && i < positions.size(); ++i)
                {
                    // Drawable - Continues if drawable is undefined or not visible
                    FROM_COMPONENT_TO_VARIABLE_CONST(drawables, i, drawable, hasDrawable);
                    if (!hasDrawable || !drawable.value().is_visible) continue;

                    // ZIndex - Continues if (zIndex != currentZIndex)
                    FROM_COMPONENT_TO_VARIABLE_CONST(zIndexes, i, zIndexComponent, hasZIndex);
                    GameEngine::ZIndexValue const zIndex = hasZIndex ? zIndexComponent.value().zIndex : GAME_ENGINE_Z_INDEX_VALUE_DEFAULT_VALUE;
                    if (zIndex < currentZIndex)
                        continue;
                    if (zIndex != currentZIndex) {
                        if (lowestZIndex == currentZIndex || zIndex < lowestZIndex)
                            lowestZIndex = zIndex;
                        continue;
                    }

                    // Sprite - Continues if sprite is undefined or if it has no texture
                    FROM_COMPONENT_TO_VARIABLE(sprites, i, spriteComponent, hasSprite);
                    if (!hasSprite) continue;
                    sf::Sprite &sprite = spriteComponent.value().sprite;
                    if (sprite.getTexture() == nullptr) continue;

                    // Color
                    FROM_COMPONENT_TO_VARIABLE_CONST(colors, i, colorComponent, hasColor);
                    GameEngine::Color const color = hasColor ? colorComponent.value() : GameEngine::Color();
                    // Position
                    FROM_COMPONENT_TO_VARIABLE_CONST(positions, i, positionComponent, hasPosition);
                    GameEngine::Position const position = hasPosition ? positionComponent.value() : GameEngine::Position({0.0, 0.0});
                    // SpriteTextureRects
                    FROM_COMPONENT_TO_VARIABLE_CONST(spriteTextureRects, i, spriteTextureRectComponent, hasSpriteTextureRect);
                    GameEngine::SpriteTextureRect const spriteTextureRect = hasSpriteTextureRect ? spriteTextureRectComponent.value() : GameEngine::SpriteTextureRect();

                    sprite.setPosition(position.pos_x, position.pos_y);
                    if (hasColor)
                        sprite.setColor(sf::Color(color.r, color.g, color.b, color.a));
                    if (hasSpriteTextureRect)
                        sprite.setTextureRect({spriteTextureRect.left, spriteTextureRect.top, spriteTextureRect.width, spriteTextureRect.height});
                    window.draw(sprite);
                }
            } while (currentZIndex != lowestZIndex);
        }

        void initEnemy(GameEngine::Registry &r) {
            EXTRACT_COMPONENT(GameEngine::Position, positions);
            EXTRACT_COMPONENT_CONST(GameEngine::Controllable, controllables);

            for (size_t i = 0; i < positions.size(); ++i) {
                // Position - Continues if position is undefined
                FROM_COMPONENT_TO_VARIABLE(positions, i, positionComponent, hasPosition);
                if (!hasPosition) continue;
                GameEngine::Position &position = positionComponent.value();

                // Controllable - Continues if controllable is defined and controllable
                FROM_COMPONENT_TO_VARIABLE_CONST(controllables, i, controllable, hasControllable);
                if (hasControllable && controllable.value().isControllable) continue;

                position.pos_x = rand() % 1080 + 1920;
                position.pos_y = rand() % 1000;
            }
        }

        void enenemyMovementSystem(GameEngine::Registry &r) {
            auto const &velocities = r.getComponent<GameEngine::Velocity>();
            auto &positions = r.getComponent<GameEngine::Position>();
            auto const &controllables = r.getComponent<GameEngine::Controllable>();

            for (size_t i = 0; i < velocities.size() && i < positions.size(); ++i) {
                auto const &vel = velocities[i];
                auto &pos = positions[i];
                auto const &controllable = controllables[i];

                if (vel && pos && !controllable || !controllable.value().isControllable) {
                    pos.value().pos_x -= vel.value().vol_x;
                    pos.value().pos_y += rand() & 1 ? vel.value().vol_y : -vel.value().vol_y;
                }
            }
        }

        void spriteSystem(GameEngine::Registry &r) {
            auto &sprites = r.getComponent<GameEngine::Sprite>();

            for (size_t i = 0; i < sprites.size(); ++i) {
                FROM_COMPONENT_TO_VARIABLE(sprites, i, sprite, hasSprite)
                if (hasSprite && sprite.value().path != "") {
                    //std::cout << "Loading texture from " << sprite.value().path << std::endl;
                    sprite.value().texture.loadFromFile(sprite.value().path);
                    sprite.value().sprite.setTexture(sprite.value().texture);
                }
            }
        }

        void collisionSystem(GameEngine::Registry &r) {
            auto const &controllables = r.getComponent<GameEngine::Controllable>();
            auto const &positions = r.getComponent<GameEngine::Position>();
            auto &lives = r.getComponent<Life>();
            std::vector<std::size_t> players;

            for (std::size_t i = 0; i < controllables.size() && i < positions.size(); ++i) {
                auto const &controllable = controllables[i];
                auto const &pos = positions[i];
                auto const &life = lives[i];

                if (controllable && pos && life)
                    players.push_back(i);
            }

            for (auto const &player : players) {
                for (std::size_t j = 0; j < positions.size(); ++j) {
                    if (player == j)
                        continue;
                    auto const &ennemy = positions[j];
                    if (isColliding(
                        positions[player].value().pos_x,
                        positions[player].value().pos_y,
                        ennemy.value().pos_x,
                        ennemy.value().pos_y,
                        100,
                        100
                    )) {
                        if (lives[player].value().life > 0)
                            lives[player].value().life -= 1;
                        else
                            std::cout << "Dead" << std::endl;//killEntity
                    }
                }
            }
        }



        void attackSystem(GameEngine::Registry &r) {
            auto &positions = r.getComponent<GameEngine::Position>();
            auto &controllables = r.getComponent<GameEngine::Controllable>();
            bool isSpacePressedUnpressed = false;

            for (size_t i = 0; i < controllables.size(); ++i) {
                FROM_COMPONENT_TO_VARIABLE(positions, i, pos, _hasPosition);
                FROM_COMPONENT_TO_VARIABLE(controllables, i, control, _hasControllable);
                if (pos && control && control.value().isControllable) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isSpacePressedUnpressed) {
                        GameEngine::Entity bullet = r.spawnEntity();
                        r.addComponent<GameEngine::Position>(bullet, GameEngine::Position{pos.value().pos_x + 50, pos.value().pos_y + 50});
                        r.addComponent<GameEngine::Velocity>(bullet, GameEngine::Velocity{-10.0f, 0.0f});
                        r.addComponent<GameEngine::Drawable>(bullet, GameEngine::Drawable{true});
                        r.addComponent<GameEngine::Sprite>(bullet, GameEngine::Sprite{"../resources/R-Touhou/graphics/bullet.png",sf::Sprite(),sf::Texture()});
                        r.addComponent<GameEngine::ZIndex>(bullet, GameEngine::ZIndex{GAME_ENGINE_Z_INDEX_VALUE_DEFAULT_VALUE - 1});
                    }
                }
            }
            isSpacePressedUnpressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
        }

    };
}

#endif
