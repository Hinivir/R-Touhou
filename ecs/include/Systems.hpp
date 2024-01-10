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
#include "Components/Hitbox.hpp"
#include "Components/Life.hpp"
#include "Components/Position.hpp"
#include "Components/Size.hpp"
#include "Components/Sprite.hpp"
#include "Components/SpriteTextureRect.hpp"
#include "Components/Velocity.hpp"
#include "Components/ZIndex.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#define DO_COMPONENT_CONTAINS_AT(COMPONENT, ID) (ID < COMPONENT.size() && COMPONENT[ID].has_value())

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
                if (std::find(r.garbageEntities.begin(), r.garbageEntities.end(), i) != r.garbageEntities.end())
                    continue;
                // Position
                FROM_COMPONENT_TO_VARIABLE_CONST(positions, i, positionComponent, hasPosition);
                GameEngine::Position const &position = hasPosition ? positionComponent.value() : GameEngine::Position();
                // Velocity
                FROM_COMPONENT_TO_VARIABLE_CONST(velocities, i, velocityComponent, hasVelocity);
                GameEngine::Velocity const &velocity = hasVelocity ? velocityComponent.value() : GameEngine::Velocity();

                if (hasPosition && hasVelocity) {
                    std ::cerr << i << ": Position = { " << position.x << ", " << position.y
                               << " } , Velocity = { " << velocity.x << ", " << velocity.y << " }"
                               << std ::endl;
                }
            }
        }

        void controlSystem(GameEngine::Registry &r) {
            EXTRACT_COMPONENT_CONST(GameEngine::Controllable, controllables);
            EXTRACT_COMPONENT(GameEngine::Position, positions);
            EXTRACT_COMPONENT_CONST(GameEngine::Velocity, velocities);

            for (size_t i = 0; i < controllables.size() && i < positions.size(); ++i) {
                if (std::find(r.garbageEntities.begin(), r.garbageEntities.end(), i) != r.garbageEntities.end())
                    continue;
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

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && position.y > -1)
                    position.y -= velocity.y;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && position.y < 1080 - 30)
                    position.y += velocity.y;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && position.x > -1)
                    position.x -= velocity.x;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && position.x < 1920 - 30)
                    position.x += velocity.x;
            }
        }

        void drawSystem(GameEngine::Registry &r, sf::RenderWindow &window) {
            EXTRACT_COMPONENT_CONST(GameEngine::Drawable, drawables);
            EXTRACT_COMPONENT_CONST(GameEngine::Position, positions);
            EXTRACT_COMPONENT(GameEngine::Sprite, sprites);
            EXTRACT_COMPONENT_CONST(GameEngine::Color, colors);
            EXTRACT_COMPONENT_CONST(GameEngine::ZIndex, zIndexes);
            EXTRACT_COMPONENT_CONST(GameEngine::SpriteTextureAnimation, spriteTextureAnimations);
            EXTRACT_COMPONENT_CONST(GameEngine::SpriteTextureRect, spriteTextureRects);
            GameEngine::ZIndexValue lowestZIndex = GAME_ENGINE_Z_INDEX_VALUE_LOWEST_VALUE;
            GameEngine::ZIndexValue currentZIndex;

            do {
                currentZIndex = lowestZIndex;
                for (size_t i = 0; i < drawables.size() && i < positions.size(); ++i)
                {
                    if (std::find(r.garbageEntities.begin(), r.garbageEntities.end(), i) != r.garbageEntities.end())
                    continue;
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
                    sf::Vector2u const &spriteTextureSize = spriteComponent.value().texture.getSize();

                    // Color
                    FROM_COMPONENT_TO_VARIABLE_CONST(colors, i, colorComponent, hasColor);
                    GameEngine::Color const color = hasColor ? colorComponent.value() : GameEngine::Color();
                    // Position
                    FROM_COMPONENT_TO_VARIABLE_CONST(positions, i, positionComponent, hasPosition);
                    GameEngine::Position const position = hasPosition ? positionComponent.value() : GameEngine::Position({0.0, 0.0});
                    // SpriteTextureAnimation
                    FROM_COMPONENT_TO_VARIABLE_CONST(spriteTextureAnimations, i, spriteTextureAnimationComponent, hasSpriteTextureAnimation);
                    GameEngine::SpriteTextureAnimation const spriteTextureAnimation = hasSpriteTextureAnimation ? spriteTextureAnimationComponent.value() : GameEngine::SpriteTextureAnimation();
                    // SpriteTextureRects
                    FROM_COMPONENT_TO_VARIABLE_CONST(spriteTextureRects, i, spriteTextureRectComponent, hasSpriteTextureRect);
                    GameEngine::SpriteTextureRect const spriteTextureRect = hasSpriteTextureRect ? spriteTextureRectComponent.value() : GameEngine::SpriteTextureRect();

                    sf::IntRect textureRect = hasSpriteTextureRect ? sf::IntRect{spriteTextureRect.left, spriteTextureRect.top, spriteTextureRect.width, spriteTextureRect.height} : sf::IntRect{0, 0, static_cast<int>(spriteTextureSize.x), static_cast<int>(spriteTextureSize.y)};

                    sprite.setPosition(position.x, position.y);
                    if (hasColor)
                        sprite.setColor(sf::Color(color.r, color.g, color.b, color.a));
                    if (hasSpriteTextureAnimation) {
                        textureRect.width /= std::max(spriteTextureAnimation.slicing.x, 1);
                        textureRect.height /= std::max(spriteTextureAnimation.slicing.y, 1);
                        textureRect.left += spriteTextureAnimation.frame.y * textureRect.width;
                        textureRect.top += spriteTextureAnimation.frame.x * textureRect.height;
                    }
                    if (hasSpriteTextureRect || hasSpriteTextureAnimation)
                        sprite.setTextureRect(textureRect);
                    textureRect = sprite.getTextureRect();
                    window.draw(sprite);
                }
            } while (currentZIndex != lowestZIndex);
        }

        void initEnemy(GameEngine::Registry &r) {
            EXTRACT_COMPONENT(GameEngine::Position, positions);
            EXTRACT_COMPONENT_CONST(GameEngine::Controllable, controllables);
            EXTRACT_COMPONENT_CONST(GameEngine::Hitbox, hitboxes);

            for (size_t i = 0; i < positions.size(); ++i) {
                if (std::find(r.garbageEntities.begin(), r.garbageEntities.end(), i) != r.garbageEntities.end())
                    continue;
                // Position - Continues if position is undefined
                FROM_COMPONENT_TO_VARIABLE(positions, i, positionComponent, hasPosition);
                if (!hasPosition) continue;
                GameEngine::Position &position = positionComponent.value();

                // Controllable - Continues if controllable is defined and controllable
                FROM_COMPONENT_TO_VARIABLE_CONST(controllables, i, controllable, hasControllable);
                if (hasControllable && controllable.value().isControllable) continue;

                // Hitbox - Continues if hitbox is undefined
                FROM_COMPONENT_TO_VARIABLE_CONST(hitboxes, i, _hitbox, hasHitbox);
                if (!hasHitbox) continue;

                position.x = rand() % 1080 + 1920;
                position.y = rand() % 1000;
            }
        }

        void enemyMovementSystem(GameEngine::Registry &r) {
            EXTRACT_COMPONENT_CONST(GameEngine::Controllable, controllables);
            EXTRACT_COMPONENT(GameEngine::Position, positions);
            EXTRACT_COMPONENT_CONST(GameEngine::Velocity, velocities);
            EXTRACT_COMPONENT_CONST(GameEngine::Hitbox, hitboxes);

            for (size_t i = 0; i < velocities.size() && i < positions.size(); ++i) {
                if (std::find(r.garbageEntities.begin(), r.garbageEntities.end(), i) != r.garbageEntities.end())
                    continue;
                // Controllable - Continues if controllable is defined and controllable
                FROM_COMPONENT_TO_VARIABLE_CONST(controllables, i, controllable, hasControllable);
                if (hasControllable && controllable.value().isControllable) continue;
                // Position - Continues if position if undefined
                FROM_COMPONENT_TO_VARIABLE(positions, i, positionComponent, hasPosition);
                if (!hasPosition) continue;
                GameEngine::Position &position = positionComponent.value();
                // Velocity
                FROM_COMPONENT_TO_VARIABLE_CONST(velocities, i, velocityComponent, hasVelocity);
                GameEngine::Velocity const &velocity = hasVelocity ? velocityComponent.value() : GameEngine::Velocity();
                // Hitbox - Continues if hitbox is undefined
                FROM_COMPONENT_TO_VARIABLE_CONST(hitboxes, i, _hitbox, hasHitbox);
                if (!hasHitbox) continue;

                position.x -= velocity.x;
                position.y += rand() & 1 ? velocity.y : -velocity.y;
            }
        }

        // Wait new system movement Viktor
        void backgroundParallax(GameEngine::Registry &r) {
            auto const &velocities = r.getComponent<Velocity>();
            auto &positions = r.getComponent<Position>();
            auto const &controllables = r.getComponent<Controllable>();
            auto const &Hitboxes = r.getComponent<Hitbox>();

 //            for (size_t i = 0; i < velocities.size() && i < positions.size(); ++i) {
            auto const &vel = velocities[0];
            auto &pos = positions[0];
            auto const &controllable = controllables[0];
            auto const &hitbox = Hitboxes[0];

            if (vel && pos && !controllable && hitbox) {
                pos.value().x -= vel.value().x;
                pos.value().y += rand() & 1 ? vel.value().y : -vel.value().y;
            }
 //            }
         }

        void spriteSystem(GameEngine::Registry &r) {
            EXTRACT_COMPONENT(GameEngine::Sprite, sprites);
            EXTRACT_COMPONENT_CONST(GameEngine::Size, sizes);

            for (size_t i = 0; i < sprites.size(); ++i) {
                if (std::find(r.garbageEntities.begin(), r.garbageEntities.end(), i) != r.garbageEntities.end())
                    continue;
                // Sprite - Continues if sprite is undefined or if it has no path
                FROM_COMPONENT_TO_VARIABLE(sprites, i, spriteComponent, hasSprite);
                if (!hasSprite) continue;
                GameEngine::Sprite &sprite = spriteComponent.value();
                std::string const &path = sprite.path;
                if (path == "") continue;

                sprite.texture.loadFromFile(sprite.path);
                sprite.sprite.setTexture(sprite.texture);

                // Size
                FROM_COMPONENT_TO_VARIABLE_CONST(sizes, i, size, hasSize);
                if (hasSize)
                    sprite.sprite.setScale(size.value().width / sprite.texture.getSize().x, size.value().height / sprite.texture.getSize().y);
            }
        }

        void collisionSystem(GameEngine::Registry &r) {
            EXTRACT_COMPONENT_CONST(GameEngine::Controllable, controllables);
            EXTRACT_COMPONENT_CONST(GameEngine::Position, positions);
            EXTRACT_COMPONENT_CONST(GameEngine::Hitbox, hitboxes);
            EXTRACT_COMPONENT(GameEngine::Life, lives);
            std::vector<std::size_t> players;

            for (std::size_t i = 0; i < controllables.size() && i < positions.size(); ++i) {
                if (std::find(r.garbageEntities.begin(), r.garbageEntities.end(), i) != r.garbageEntities.end())
                    continue;
                // Controllable - Continues if controllable is undefined or not controllable
                FROM_COMPONENT_TO_VARIABLE_CONST(controllables, i, controllable, hasControllable);
                if (!hasControllable || !controllable.value().isControllable) continue;

                // Position - Continues if position is undefined
                FROM_COMPONENT_TO_VARIABLE_CONST(positions, i, _position, hasPosition);
                if (!hasPosition) continue;

                // Life - Continues if life is undefined
                FROM_COMPONENT_TO_VARIABLE_CONST(lives, i, _life, hasLife);
                if (!hasLife) continue;

                // Hitbox - Continues if hitbox is undefined
                FROM_COMPONENT_TO_VARIABLE_CONST(hitboxes, i, _hitbox, hasHitbox);
                if (!hasHitbox) continue;

                players.push_back(i);
            }

            for (auto const &playerID : players) {
                for (std::size_t j = 0; j < positions.size(); ++j) {
                    if (std::find(r.garbageEntities.begin(), r.garbageEntities.end(), j) != r.garbageEntities.end())
                        continue;
                    if (playerID == j)
                        continue;
                    // Enemy, Player and Lives - Continues if one of these is undefined
                    FROM_COMPONENT_TO_VARIABLE_CONST(positions, j, enemy, hasEnemy);
                    FROM_COMPONENT_TO_VARIABLE_CONST(hitboxes, j, _enemyHitbox, hasEnemyHitbox);
                    FROM_COMPONENT_TO_VARIABLE_CONST(positions, playerID, player, hasPlayer);
                    FROM_COMPONENT_TO_VARIABLE(lives, playerID, lifeComponent, hasLife);
                    if (!hasEnemy || !hasPlayer || !hasLife || !hasEnemyHitbox)
                        continue;
                    GameEngine::Life &life = lifeComponent.value();

                    if (isColliding(
                        player.value().x,
                        player.value().y,
                        enemy.value().x,
                        enemy.value().y,
                        100,
                        100
                    )) {
                        if (life.life > 0)
                            life.life -= 1;
                        else {
                            r.garbageEntities.push_back(std::size_t(playerID));
                            std::cout << "Dead" << std::endl;//killEntity
                        }
                    }
                }
            }
        }



        void attackSystem(GameEngine::Registry &r) {
            auto &positions = r.getComponent<GameEngine::Position>();
            auto &controllables = r.getComponent<GameEngine::Controllable>();
            bool isSpacePressedUnpressed = false;

            for (size_t i = 0; i < controllables.size(); ++i) {
                if (std::find(r.garbageEntities.begin(), r.garbageEntities.end(), i) != r.garbageEntities.end())
                    continue;
                FROM_COMPONENT_TO_VARIABLE(positions, i, pos, _hasPosition);
                FROM_COMPONENT_TO_VARIABLE(controllables, i, control, _hasControllable);
                if (pos && control && control.value().isControllable) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isSpacePressedUnpressed) {
                        GameEngine::Entity bullet = r.spawnEntity();
                        r.addComponent<GameEngine::Position>(bullet, GameEngine::Position{pos.value().x + 50, pos.value().y + 50});
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
