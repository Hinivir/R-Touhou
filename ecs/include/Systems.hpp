/*
** EPITECH PROJECT, 2023
** R-Touhou_Bootstrap
** File description:
** Systems.hpp
*/

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "Registry.hpp"
#include "Components/Position.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#define DO_COMPONENT_CONTAINS_AT(COMPONENT, ID) (i < COMPONENT.size() && COMPONENT[ID].has_value())

#define FROM_COMPONENT_TO_VARIABLE(COMPONENT, ID, VARIABLE, VARIABLE_HAS) \
    bool const VARIABLE_HAS = DO_COMPONENT_CONTAINS_AT(COMPONENT, ID); auto &VARIABLE = COMPONENT[VARIABLE_HAS ? ID : 0];
#define FROM_COMPONENT_TO_VARIABLE_CONST(COMPONENT, ID, VARIABLE, VARIABLE_HAS) \
    bool const VARIABLE_HAS = DO_COMPONENT_CONTAINS_AT(COMPONENT, ID); auto const &VARIABLE = COMPONENT[VARIABLE_HAS ? ID : 0];

namespace GameEngine
{

    class System
    {
      public:
        System() = default;
        ~System() = default;

        void loggingSystem(GameEngine::Registry &r) {
            auto const &positions = r.getComponent<GameEngine::Position>();
            auto const &velocities = r.getComponent<GameEngine::Velocity>();

            for (size_t i = 0; i < positions.size() && i < velocities.size(); ++i) {
                auto const &pos = positions[i];
                auto const &vel = velocities[i];
                if (pos && vel) {
                    std ::cerr << i << ": Position = { " << pos.value().pos_x << ", " << pos.value().pos_y
                               << " } , Velocity = { " << vel.value().vol_x << ", " << vel.value().vol_y << " }"
                               << std ::endl;
                }
            }
        }

        void controlSystem(GameEngine::Registry &r) {
            auto const &controllables = r.getComponent<Controllable>();
            auto &positions = r.getComponent<Position>();
            auto velocities = r.getComponent<Velocity>();

            for (size_t i = 0; i < controllables.size() && i < positions.size(); ++i) {
                auto &controllable = controllables[i];
                auto &pos = positions[i];
                auto &vel = velocities[i];

                if ((controllable || controllable.value().isControllable) && vel) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                        pos.value().pos_y -= vel.value().vol_y;
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                        pos.value().pos_y += vel.value().vol_y;
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                        pos.value().pos_x -= vel.value().vol_x;
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                        pos.value().pos_x += vel.value().vol_x;
                }
            }
        }

        void drawSystem(GameEngine::Registry &r, sf::RenderWindow &window) {
            auto &drawables = r.getComponent<Drawable>();
            auto &positions = r.getComponent<Position>();
            auto &sprites = r.getComponent<Sprite>();
            auto &colors = r.getComponent<Color>();
            auto &zIndexes = r.getComponent<ZIndex>();
            GameEngine::ZIndexValue lowestZIndex = GAME_ENGINE_Z_INDEX_VALUE_LOWEST_VALUE;
            GameEngine::ZIndexValue currentZIndex;

            do {
                currentZIndex = lowestZIndex;
                for (size_t i = 0; i < drawables.size() && i < positions.size(); ++i)
                {
                    FROM_COMPONENT_TO_VARIABLE(drawables, i, drawable, hasDrawable);
                    if (!hasDrawable || drawable.value().is_visible) continue;
                    FROM_COMPONENT_TO_VARIABLE(positions, i, position, hasPosition);
                    FROM_COMPONENT_TO_VARIABLE(sprites, i, sprite, hasSprite);
                    FROM_COMPONENT_TO_VARIABLE(colors, i, color, hasColor);
                    FROM_COMPONENT_TO_VARIABLE(zIndexes, i, zIndex, hasZIndex);
                    GameEngine::ZIndexValue zIndexValue = hasZIndex ? zIndex.value().zIndex : GAME_ENGINE_Z_INDEX_VALUE_DEFAULT_VALUE;
                    GameEngine::Position pos = hasPosition ? position.value() : GameEngine::Position({0.0, 0.0});

                    if (zIndexValue < currentZIndex)
                        continue;
                    if (zIndexValue != currentZIndex) {
                        if (lowestZIndex == currentZIndex || zIndexValue < lowestZIndex)
                            lowestZIndex = zIndexValue;
                        continue;
                    }
                    if (hasSprite && sprite.value().sprite.getTexture() != nullptr) {
                        sprite.value().sprite.setPosition(pos.pos_x, pos.pos_y);
                        if (hasColor)
                            sprite.value().sprite.setColor(sf::Color(color.value().r, color.value().g, color.value().b, color.value().a));
                        window.draw(sprite.value().sprite);
                    }
                }
            } while (currentZIndex != lowestZIndex);
        }

        void initEnemy(GameEngine::Registry &r) {
            auto &positions = r.getComponent<Position>();
            auto const &controllables = r.getComponent<Controllable>();
            std::size_t y = 0;

            for (size_t i = 0; i < positions.size(); ++i) {
                y = 0;
                auto &pos = positions[i];
                auto const &controllable = controllables[i];

                if (pos && !controllable || !controllable.value().isControllable) {
                    pos.value().pos_x = rand() % 1000;
                    y = rand() % 1000;
                    if (y > 1920)
                        y = rand() % 1000;
                    pos.value().pos_y = rand() % 1000;
                }
            }
        }

        void enenemyMovementSystem(GameEngine::Registry &r) {
            auto const &velocities = r.getComponent<Velocity>();
            auto &positions = r.getComponent<Position>();
            auto const &controllables = r.getComponent<Controllable>();

            for (size_t i = 0; i < velocities.size() && i < positions.size(); ++i) {
                auto const &vel = velocities[i];
                auto &pos = positions[i];
                auto const &controllable = controllables[i];

                if (vel && pos && !controllable || !controllable.value().isControllable) {
                    pos.value().pos_x += vel.value().vol_x;
                    pos.value().pos_y += rand() & 1 ? vel.value().vol_y : -vel.value().vol_y;
                }
            }
        }

        void spriteSystem(GameEngine::Registry &r) {
            auto &sprites = r.getComponent<Sprite>();

            for (size_t i = 0; i < sprites.size(); ++i) {
                auto &sprite = sprites[i];
                if (!sprite.value().path.empty()) {
                    sprite.value().texture.loadFromFile(sprite.value().path);
                    sprite.value().sprite.setTexture(sprite.value().texture);
                }
            }
        }

    };
}

#endif
