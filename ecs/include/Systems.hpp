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

        void positionSystem(GameEngine::Registry &r) {
            auto &positions = r.getComponent<GameEngine::Position>();
            auto const &velocities = r.getComponent<GameEngine::Velocity>();

            for (size_t i = 0; i < positions.size() && i < velocities.size(); ++i) {
                auto &pos = positions[i];
                auto &vel = velocities[i];
                if (pos && vel) {
                    pos.value().pos_x += vel.value().vol_x;
                    pos.value().pos_y += vel.value().vol_y;
                }
            }
        }

        void controlSystem(GameEngine::Registry &r) {
            auto const &controllables = r.getComponent<Controllable>();
            auto &velocities = r.getComponent<Velocity>();

            for (size_t i = 0; i < controllables.size() && i < velocities.size(); ++i) {
                auto &controllable = controllables[i];
                auto &vel = velocities[i];

                if (controllable && vel) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                        vel.value().vol_y -= 1;
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                        vel.value().vol_y += 1;
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                        vel.value().vol_x -= 1;
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                        vel.value().vol_x += 1;
                }
            }
        }

        void drawSystem(GameEngine::Registry &r, sf::RenderWindow &window) {
            auto &drawables = r.getComponent<Drawable>();
            auto &positions = r.getComponent<Position>();
            auto &sprites = r.getComponent<Sprite>();
            auto &colors = r.getComponent<Color>();

            for (size_t i = 0; i < drawables.size() && i < positions.size(); ++i)
            {
                auto &drawable = drawables[i];
                auto &pos = positions[i];
                auto &sprite = sprites[i];
                auto &color = colors[i];

                if (drawable && pos) {
                    if (sprite.value().sprite.getTexture() != nullptr) {
                        sprite.value().sprite.setPosition(pos.value().pos_x, pos.value().pos_y);
                        window.draw(sprite.value().sprite);
                        std::cout << "Drawing entity at position (" << pos.value().pos_x << ", " << pos.value().pos_y << ")" << std::endl;
                    } else if (color) {
                        sf::RectangleShape rectangle(sf::Vector2f(50, 50));
                        rectangle.setPosition(pos.value().pos_x, pos.value().pos_y);
                        rectangle.setFillColor(sf::Color(color.value().r, color.value().g, color.value().b, color.value().a));
                        window.draw(rectangle);
                        std::cout << "Drawing entity at position (" << pos.value().pos_x << ", " << pos.value().pos_y << ")" << std::endl;
                    } else {
                        throw std::runtime_error("No drawable component found");
                    }
                }
            }
        }

        void spriteSystem(GameEngine::Registry &r, std::size_t entityId) {
            auto entity = r.getEntityById(entityId);
            auto &sprites = r.getComponent<Sprite>();
            if (entity == -1 || !sprites[entityId])
                return;
            auto &sprite = sprites[entityId];
            sprite.value().texture.loadFromFile(sprite.value().path);
            sprite.value().sprite.setTexture(sprite.value().texture);
        }

    };
}

#endif
