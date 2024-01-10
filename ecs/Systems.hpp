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
#include "Components/SpriteTextureAnimation.hpp"
#include "Components/SpriteTextureRect.hpp"
#include "Components/Velocity.hpp"
#include "Components/ZIndex.hpp"
#include "Components/Projectile.hpp"
#include "Components/Path.hpp"
#include "Components/Text.hpp"
#include "Components/Window.hpp"

#include <list>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>

#define DO_COMPONENT_CONTAINS_AT(COMPONENT, ID) (ID < COMPONENT.size() && COMPONENT[ID].has_value())

#define EXTRACT_COMPONENT(COMPONENT, VARIABLE) auto &VARIABLE = r.getComponent<COMPONENT>()
#define EXTRACT_COMPONENT_CONST(COMPONENT, VARIABLE) auto const &VARIABLE = r.getComponent<COMPONENT>()

#define FROM_COMPONENT_TO_VARIABLE(COMPONENT, ID, VARIABLE, VARIABLE_HAS) \
    bool const VARIABLE_HAS = DO_COMPONENT_CONTAINS_AT(COMPONENT, ID); auto &VARIABLE = COMPONENT[VARIABLE_HAS ? ID : 0];
#define FROM_COMPONENT_TO_VARIABLE_CONST(COMPONENT, ID, VARIABLE, VARIABLE_HAS) \
    bool const VARIABLE_HAS = DO_COMPONENT_CONTAINS_AT(COMPONENT, ID); auto const &VARIABLE = COMPONENT[VARIABLE_HAS ? ID : 0];

bool isColliding(
    std::size_t x1,
    std::size_t y1,
    std::size_t x2,
    std::size_t y2,
    std::size_t width1,
    std::size_t height1,
    std::size_t width2,
    std::size_t height2
) {
    return (
        x1 < x2 + width2 &&
        x1 + width1 > x2 &&
        y1 < y2 + height2 &&
        y1 + height1 > y2
    );
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

        void controlSystem(GameEngine::Registry &r)
        {
            EXTRACT_COMPONENT_CONST(GameEngine::Controllable, controllables);
            EXTRACT_COMPONENT(GameEngine::Position, positions);
            EXTRACT_COMPONENT_CONST(GameEngine::Velocity, velocities);
            EXTRACT_COMPONENT_CONST(GameEngine::Size, sizes);

            for (size_t i = 0; i < controllables.size() && i < positions.size(); ++i) {
                if (std::find(r.garbageEntities.begin(), r.garbageEntities.end(), i) != r.garbageEntities.end())
                    continue;
                // Controllable - Continues if controllable is undefined or no controllable
                FROM_COMPONENT_TO_VARIABLE_CONST(controllables, i, controllable, hasControllable);
                if (!hasControllable || !controllable.value().isControllable) continue;
                // Position - Continues if position is undefined
                FROM_COMPONENT_TO_VARIABLE(positions, i, positionComponent, hasPosition);
                //if (!hasPosition) continue;
                GameEngine::Position &position = positionComponent.value();
                // Velocity
                FROM_COMPONENT_TO_VARIABLE_CONST(velocities, i, velocityComponent, hasVelocity);
                GameEngine::Velocity const &velocity = hasVelocity ? velocityComponent.value() : GameEngine::Velocity();
                // Size
                FROM_COMPONENT_TO_VARIABLE_CONST(sizes, i, sizeComponent, hasSize);
                GameEngine::Size const &size = hasSize ? sizeComponent.value() : GameEngine::Size();

                if ((controllable && controllable.value().isControllable) && hasVelocity) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                        if (position.y > 50)
                            position.y -= 10;

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                        if (position.y < WINDOW_HEIGHT - size.width - 50)
                            position.y += 10;

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                        if (position.x > 0)
                            position.x -= 10;

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                        if (position.x < WINDOW_WIDTH - size.width)
                            position.x += 10;
                }
            }
        }

        void drawSystem(GameEngine::Registry &r, sf::RenderWindow &window)
        {
            EXTRACT_COMPONENT_CONST(GameEngine::Drawable, drawables);
            EXTRACT_COMPONENT_CONST(GameEngine::Position, positions);
            EXTRACT_COMPONENT(GameEngine::Sprite, sprites);
            EXTRACT_COMPONENT_CONST(GameEngine::Color, colors);
            EXTRACT_COMPONENT_CONST(GameEngine::ZIndex, zIndexes);
            EXTRACT_COMPONENT_CONST(GameEngine::SpriteTextureAnimation, spriteTextureAnimations);
            EXTRACT_COMPONENT_CONST(GameEngine::SpriteTextureRect, spriteTextureRects);
            EXTRACT_COMPONENT(GameEngine::Text, texts);
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
                    if (!hasDrawable || !drawable.value().isVisible) continue ;

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

                    // Color
                    FROM_COMPONENT_TO_VARIABLE_CONST(colors, i, colorComponent, hasColor);
                    GameEngine::Color const color = hasColor ? colorComponent.value() : GameEngine::Color();
                    // Position
                    FROM_COMPONENT_TO_VARIABLE_CONST(positions, i, positionComponent, hasPosition);
                    GameEngine::Position const position = hasPosition ? positionComponent.value() : GameEngine::Position({0.0, 0.0});
                    // Sprite
                    FROM_COMPONENT_TO_VARIABLE(sprites, i, spriteComponent, hasSprite);
                    // SpriteTextureAnimation
                    FROM_COMPONENT_TO_VARIABLE_CONST(spriteTextureAnimations, i, spriteTextureAnimationComponent, hasSpriteTextureAnimation);
                    GameEngine::SpriteTextureAnimation const spriteTextureAnimation = hasSpriteTextureAnimation ? spriteTextureAnimationComponent.value() : GameEngine::SpriteTextureAnimation();
                    // SpriteTextureRects
                    FROM_COMPONENT_TO_VARIABLE_CONST(spriteTextureRects, i, spriteTextureRectComponent, hasSpriteTextureRect);
                    GameEngine::SpriteTextureRect const spriteTextureRect = hasSpriteTextureRect ? spriteTextureRectComponent.value() : GameEngine::SpriteTextureRect();
                    // Text
                    FROM_COMPONENT_TO_VARIABLE(texts, i, textComponent, hasText);

                    if (hasText) {
                        GameEngine::Text &text = textComponent.value();
                        if (hasColor)
                            text.text.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
                        if (!text.isLoaded) {
                            if (text.font.loadFromFile(text.fontPath))
                                text.text.setFont(text.font);
                            if (text.text.getFont() == nullptr) {
                                goto drawSystemEndOfHasText;
                            }
                            text.isLoaded = true;
                        }
                        text.text.setString(text.string);
                        text.text.setPosition(position.x, position.y);
                        text.text.setCharacterSize(text.fontSize);
                        window.draw(text.text);
                    }
                    drawSystemEndOfHasText:
                    if (hasSprite) {
                        // Sprite
                        sf::Sprite &sprite = spriteComponent.value().sprite;

                        // SpriteTextureAnimation
                        FROM_COMPONENT_TO_VARIABLE_CONST(spriteTextureAnimations, i, spriteTextureAnimationComponent, hasSpriteTextureAnimation);
                        GameEngine::SpriteTextureAnimation const spriteTextureAnimation = hasSpriteTextureAnimation ? spriteTextureAnimationComponent.value() : GameEngine::SpriteTextureAnimation();

                        // SpriteTextureRects
                        FROM_COMPONENT_TO_VARIABLE_CONST(spriteTextureRects, i, spriteTextureRectComponent, hasSpriteTextureRect);
                        GameEngine::SpriteTextureRect const spriteTextureRect = hasSpriteTextureRect ? spriteTextureRectComponent.value() : GameEngine::SpriteTextureRect();

                        //
                        sf::Vector2u const &spriteTextureSize = spriteComponent.value().texture.getSize();
                        sf::IntRect textureRect = hasSpriteTextureRect ? sf::IntRect{spriteTextureRect.left, spriteTextureRect.top, spriteTextureRect.width, spriteTextureRect.height} : sf::IntRect{0, 0, static_cast<int>(spriteTextureSize.x), static_cast<int>(spriteTextureSize.y)};

                        if (sprite.getTexture() == nullptr) continue; //goto drawSystemEndOfHasSprite; (removed because pointing at the end of a for() loop)
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
                    //drawSystemEndOfHasSprite: (removed because at the end of a for() loop)
                }
            } while (currentZIndex != lowestZIndex);
        }

        void initEnemy(GameEngine::Registry &r)
        {
            EXTRACT_COMPONENT(GameEngine::Position, positions);
            EXTRACT_COMPONENT_CONST(GameEngine::Controllable, controllables);
            EXTRACT_COMPONENT_CONST(GameEngine::Hitbox, hitboxes);
            EXTRACT_COMPONENT(GameEngine::Path, paths);
            EXTRACT_COMPONENT_CONST(GameEngine::Size, sizes);
            EXTRACT_COMPONENT(GameEngine::Projectile, projectiles);

            for (size_t i = 0; i < positions.size(); ++i) {
                if (std::find(r.garbageEntities.begin(), r.garbageEntities.end(), i) != r.garbageEntities.end())
                    continue;
                // Position - Continues if position is undefined
                FROM_COMPONENT_TO_VARIABLE(positions, i, positionComponent, hasPosition);
                if (!hasPosition)
                    continue;
                GameEngine::Position &position = positionComponent.value();

                // Controllable - Continues if controllable is defined and controllable
                FROM_COMPONENT_TO_VARIABLE_CONST(controllables, i, controllable, hasControllable);
                if (hasControllable && controllable.value().isControllable)
                    continue;

                // Hitbox - Continues if hitbox is undefined
                FROM_COMPONENT_TO_VARIABLE_CONST(hitboxes, i, hitbox, hasHitbox);
                if (!hasHitbox)
                    continue;

                // Path - Continues if path is not defined
                FROM_COMPONENT_TO_VARIABLE(paths, i, pathComponent, hasPath);
                if (!hasPath)
                    continue;

                FROM_COMPONENT_TO_VARIABLE_CONST(sizes, i, sizeComponent, hasSize)

                FROM_COMPONENT_TO_VARIABLE(projectiles, i, projectileComponent, hasProjectile);
                // if (hasProjectile) continue;
                GameEngine::Projectile &projectile = projectileComponent.value();

                GameEngine::Path &path = pathComponent.value();
                GameEngine::Size const &size = sizeComponent.value();
                position.x = rand() % 1080 + 1920;
                position.y = rand() % 1000;
                path.startX = position.x;
                path.startY = position.y;
                path.endY = -100 + size.width;
                projectile.isProjectile = false;
            }
        }

        void movementSystem(GameEngine::Registry &r)
        {
            EXTRACT_COMPONENT_CONST(GameEngine::Velocity, velocities);
            EXTRACT_COMPONENT(GameEngine::Position, positions);
            EXTRACT_COMPONENT_CONST(GameEngine::Projectile, projectiles);
            EXTRACT_COMPONENT_CONST(GameEngine::Controllable, controllables);
            EXTRACT_COMPONENT_CONST(GameEngine::Path, paths);

            for (size_t i = 0; i < velocities.size() && i < positions.size(); ++i) {
                FROM_COMPONENT_TO_VARIABLE_CONST(velocities, i, velociyComponent, hasVelocity);
                GameEngine::Velocity const &velocity = velociyComponent.value();
                FROM_COMPONENT_TO_VARIABLE(positions, i, positionComponent, hasPosition);
                GameEngine::Position &position = positionComponent.value();
                FROM_COMPONENT_TO_VARIABLE_CONST(controllables, i, controllableComponent, hasControllable);
                GameEngine::Controllable const &controllable = controllableComponent.value();
                FROM_COMPONENT_TO_VARIABLE_CONST(projectiles, i, projectileComponent, hasProjectile);
                GameEngine::Projectile const &projectile = projectileComponent.value();
                FROM_COMPONENT_TO_VARIABLE_CONST(paths, i, pathComponent, hasPath);
                if (!hasPath) continue;
                GameEngine::Path const &path = pathComponent.value();

                if (
                    hasVelocity && hasPosition && !hasControllable && !hasProjectile) {

                    // std::cout << "OK9999" << std::endl;
                    position.x -= 10;

                } else if (
                    hasVelocity && hasPosition && hasPath &&
                    (!hasControllable || !controllable.isControllable) &&
                    (!hasProjectile || !projectile.isProjectile)) {

                        position.x -= velocity.x;
                        position.y -= velocity.y;

                } else if (
                    hasVelocity && hasPosition && hasPath
                    && !hasControllable && hasProjectile) {

                        position.x += velocity.x;
                        position.y += velocity.y;

                }
            }
        }

        // Wait new system movement Viktor
        void backgroundParallax(GameEngine::Registry &r)
        {
            EXTRACT_COMPONENT_CONST(GameEngine::Velocity, velocities);
            EXTRACT_COMPONENT(GameEngine::Position, positions);
            EXTRACT_COMPONENT_CONST(GameEngine::Controllable, controllables);

            //for (size_t i = 0; i < velocities.size() && i < positions.size(); ++i) {
            FROM_COMPONENT_TO_VARIABLE_CONST(velocities, 0, velocityComponent, hasVelocity);
            GameEngine::Velocity const &velocity = velocityComponent.value();
            FROM_COMPONENT_TO_VARIABLE(positions, 0, positionComponent, hasPosition);
            GameEngine::Position &position = positionComponent.value();
            FROM_COMPONENT_TO_VARIABLE_CONST(controllables, 0, controllableComponent, hasControllable);
            GameEngine::Controllable const &controllable = controllableComponent.value();

            if (hasVelocity && hasPosition && !hasControllable) {
                position.x -= velocity.x;
                position.y += rand() & 1 ? velocity.y : -velocity.y;
            }
            //}
         }

        void spriteSystem(GameEngine::Registry &r)
        {
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

        void collisionSystem(GameEngine::Registry &r)
        {
            EXTRACT_COMPONENT_CONST(GameEngine::Controllable, controllables);
            EXTRACT_COMPONENT_CONST(GameEngine::Position, positions);
            EXTRACT_COMPONENT_CONST(GameEngine::Hitbox, hitboxes);
            EXTRACT_COMPONENT_CONST(GameEngine::Size, sizes);
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
                // Player - Continues if player is undefined
                FROM_COMPONENT_TO_VARIABLE_CONST(positions, playerID, playerPosition, hasPlayerPosition);
                FROM_COMPONENT_TO_VARIABLE_CONST(sizes, playerID, playerSize, hasPlayerHitbox);
                FROM_COMPONENT_TO_VARIABLE(lives, playerID, playerLife, hasLife);
                if (!hasPlayerPosition || !hasPlayerHitbox || !hasLife) continue;

                for (std::size_t j = 0; j < positions.size(); ++j) {
                    if (std::find(r.garbageEntities.begin(), r.garbageEntities.end(), j) != r.garbageEntities.end())
                        continue;
                    if (playerID == j)
                        continue;
                    // Enemy, Player and Lives - Continues if one of these is undefined
                    FROM_COMPONENT_TO_VARIABLE_CONST(positions, j, enemyPosition, hasEnemyPosition);
                    FROM_COMPONENT_TO_VARIABLE_CONST(sizes, j, enemySize, hasEnemySize);
                    FROM_COMPONENT_TO_VARIABLE_CONST(hitboxes, j, enemyHitbox, hasEnemyHitbox);
                    if (!hasEnemyPosition || !hasEnemySize || !hasEnemyHitbox) continue;

                    GameEngine::Life &life = playerLife.value();
                    if (isColliding(
                        playerPosition.value().x,
                        playerPosition.value().y,
                        enemyPosition.value().x,
                        enemyPosition.value().y,
                        playerSize.value().width,
                        playerSize.value().height,
                        enemySize.value().width,
                        enemySize.value().height
                    )) {
                        if (life.life > 0) {
                            life.life -= 1;
                            break;
                        } else {
                            r.garbageEntities.push_back(std::size_t(playerID));
                            break;
                        }
                    }
                }
            }
        }

        void attackSystem(GameEngine::Registry &r) {
            auto &positions = r.getComponent<GameEngine::Position>();
            auto &controllables = r.getComponent<GameEngine::Controllable>();
            EXTRACT_COMPONENT(GameEngine::Size, sizes);
            bool isSpacePressedUnpressed = false;

            for (size_t i = 0; i < controllables.size(); ++i) {
                if (std::find(r.garbageEntities.begin(), r.garbageEntities.end(), i) != r.garbageEntities.end())
                    continue;
                FROM_COMPONENT_TO_VARIABLE(positions, i, positionComponent, _hasPosition);
                GameEngine::Position &position = positionComponent.value();
                FROM_COMPONENT_TO_VARIABLE(controllables, i, control, _hasControllable);
                FROM_COMPONENT_TO_VARIABLE(sizes, i, size, _hasSize)

                if (_hasPosition && _hasControllable && control.value().isControllable) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isSpacePressedUnpressed) {
                        GameEngine::Entity bullet = r.spawnEntity();
                        r.addComponent<GameEngine::Position>(bullet, GameEngine::Position{position.x + size.value().height, position.y + size.value().width / 2});
                        r.addComponent<GameEngine::Velocity>(bullet, GameEngine::Velocity{100.0f, 0.0f});
                        r.addComponent<GameEngine::Drawable>(bullet, GameEngine::Drawable{true});
                        r.addComponent<GameEngine::Sprite>(bullet, GameEngine::Sprite{"../games/resources/R-Touhou/graphics/bullet.png",sf::Sprite(),sf::Texture()});
                        r.addComponent<GameEngine::ZIndex>(bullet, GameEngine::ZIndex{GAME_ENGINE_Z_INDEX_VALUE_DEFAULT_VALUE - 1});
                        r.addComponent<GameEngine::Projectile>(bullet, GameEngine::Projectile{true});
                        r.addComponent<GameEngine::Path>(bullet, GameEngine::Path{position.x + size.value().height, position.y + size.value().width / 2, 1920 + 50, 1080 + 50});
                    }
                }
                isSpacePressedUnpressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
            }
        }


        void deleteEntitiesSystem(GameEngine::Registry &r)
        {
            auto &positions = r.getComponent<Position>();
            auto &paths = r.getComponent<Path>();
            auto &projectiles = r.getComponent<Projectile>();

            for (size_t i = 0; i < positions.size(); ++i) {
                FROM_COMPONENT_TO_VARIABLE(positions, i, pos, _hasPosition);
                FROM_COMPONENT_TO_VARIABLE(paths, i, path, _hasPath);
                FROM_COMPONENT_TO_VARIABLE(projectiles, i, projectile, _hasProjectile);
                if (_hasPosition && _hasPath) {
                    if (_hasProjectile && projectile.value().isProjectile) {
                        if (pos.value().x >= path.value().endX || pos.value().y >= path.value().endY) {
                            auto entityId = r.getEntityById(i);
                            r.garbageEntities.push_back((std::size_t)entityId);
                        }
                    } else {
                        if (pos.value().x <= path.value().endX || pos.value().y <= path.value().endY) {
                            auto entityId = r.getEntityById(i);
                            r.garbageEntities.push_back((std::size_t)entityId);
                        }
                    }
                }
            }
        }
    };
}

#endif
