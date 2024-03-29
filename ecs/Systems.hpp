/*
** EPITECH PROJECT, 2023
** R-Touhou_Bootstrap
** File description:
** Systems.hpp
*/

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "Registry.hpp"
#include "Components/Components.hpp"

#include "Macros/Systems.hpp"

#include <list>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

namespace GameEngine
{

    class SystemGroup
    {
      public:
        SystemGroup() = default;
        ~SystemGroup() = default;

        bool isColliding(std::size_t x1, std::size_t y1, std::size_t x2, std::size_t y2, std::size_t width1,
            std::size_t height1, std::size_t width2, std::size_t height2)
        {
            return (x1 < x2 + width2 && x1 + width1 > x2 && y1 < y2 + height2 && y1 + height1 > y2);
        }

        void loggingSystem(GameEngine::Registry &REGISTRY_DEFAULT_NAME)
        {
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
                    std ::cerr << i << ": Position = { " << position.x << ", " << position.y << " } , Velocity = { "
                               << velocity.x << ", " << velocity.y << " }" << std ::endl;
                }
            }
        }

        //        void controlSystem1P(GameEngine::Registry

        void controlSystem(GameEngine::Registry &REGISTRY_DEFAULT_NAME)
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
                if (!hasControllable || !controllable.value().isControllable)
                    continue;
                // Position - Continues if position is undefined
                FROM_COMPONENT_TO_VARIABLE(positions, i, positionComponent, hasPosition);
                // if (!hasPosition) continue;
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

        void initEnemy(GameEngine::Registry &REGISTRY_DEFAULT_NAME)
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
                if (position.x != 30.0f && position.y != 30.0f)
                    continue;

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
                if (hasProjectile)
                    continue;

                GameEngine::Path &path = pathComponent.value();
                GameEngine::Size const &size = sizeComponent.value();
                // useless
                position.x = rand() % 1080 + 1920;
                position.y = rand() % 1000 - 50;
                if (position.y < 50)
                    position.y = 50;
                if (position.y > 1030)
                    position.y = 1030;
                //
                path.startX = position.x;
                path.startY = position.y;
                path.endY = -100 + size.width;
            }
        }

        void initEnemy(GameEngine::Registry &REGISTRY_DEFAULT_NAME, std::vector<std::pair<float, float>> &pos)
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
                if (position.x != 30.0f && position.y != 30.0f)
                    continue;

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
                if (hasProjectile)
                    continue;

                GameEngine::Path &path = pathComponent.value();
                GameEngine::Size const &size = sizeComponent.value();
                position.x = pos[i].first;
                position.y = pos[i].second;
                path.startX = position.x;
                path.startY = position.y;
                path.endY = -100 + size.width;
            }
        }

        void movementSystem(GameEngine::Registry &REGISTRY_DEFAULT_NAME)
        {
            EXTRACT_COMPONENT_CONST(GameEngine::Velocity, velocities);
            EXTRACT_COMPONENT(GameEngine::Position, positions);
            EXTRACT_COMPONENT_CONST(GameEngine::Projectile, projectiles);
            EXTRACT_COMPONENT_CONST(GameEngine::Controllable, controllables);
            EXTRACT_COMPONENT_CONST(GameEngine::Path, paths);
            EXTRACT_COMPONENT_CONST(GameEngine::Size, sizes);

            for (size_t i = 0; i < velocities.size() && i < positions.size(); ++i) {
                FROM_COMPONENT_TO_VARIABLE_CONST(velocities, i, velociyComponent, hasVelocity);
                GameEngine::Velocity const &velocity = velociyComponent.value();
                FROM_COMPONENT_TO_VARIABLE(positions, i, positionComponent, hasPosition);
                GameEngine::Position &position = positionComponent.value();
                FROM_COMPONENT_TO_VARIABLE_CONST(controllables, i, controllableComponent, hasControllable);
                GameEngine::Controllable const &controllable = controllableComponent.value();
                FROM_COMPONENT_TO_VARIABLE_CONST(projectiles, i, projectileComponent, hasProjectile);
                FROM_COMPONENT_TO_VARIABLE_CONST(paths, i, pathComponent, hasPath);
                FROM_COMPONENT_TO_VARIABLE_CONST(sizes, i, sizeComponent, hasSize);

                if (hasVelocity && hasPosition && hasPath && (!hasControllable || !controllable.isControllable) &&
                    !hasProjectile) {
                    position.x -= velocity.x;
                    position.y -= velocity.y;
                } else if (hasVelocity && hasPosition && hasPath && !hasControllable && hasProjectile) {
                    position.x += velocity.x;
                    position.y += velocity.y;
                } else if (hasVelocity && hasPosition && !hasPath && !hasControllable && !hasProjectile &&
                           sizeComponent.value().width == 1920 && sizeComponent.value().height == 1080) {
                    if (position.x < -1920) {
                        position.x = 1920;
                    }
                    position.x -= velocity.x;
                    position.x -= velocity.x;
                    position.y += rand() & 1 ? velocity.y : -velocity.y;
                    position.x -= velocity.x;
                    position.y += rand() & 1 ? velocity.y : -velocity.y;
                }
            }
        }

        void collisionSystem(GameEngine::Registry &REGISTRY_DEFAULT_NAME, int &score,
                             std::vector<int> &garbageToSend,
                             std::vector<GameEngine::Entity> playerVector,
                             std::vector<GameEngine::Entity> enemyVector,
                             std::vector<GameEngine::Entity> bulletVector)
        {
            for (auto &enemy: enemyVector) {
                for (auto &player: playerVector) {
                    if (isColliding(r.getComponent<GameEngine::Position>()[enemy].value().x,
                                r.getComponent<GameEngine::Position>()[enemy].value().y,
                                r.getComponent<GameEngine::Position>()[player].value().x,
                                r.getComponent<GameEngine::Position>()[player].value().y,
                                r.getComponent<GameEngine::Size>()[enemy].value().width,
                                r.getComponent<GameEngine::Size>()[enemy].value().height,
                                r.getComponent<GameEngine::Size>()[player].value().width,
                                r.getComponent<GameEngine::Size>()[player].value().height)) {
                                    if (r.getComponent<GameEngine::Life>()[player].value().life > 0) {
                                        r.getComponent<GameEngine::Life>()[player].value().life -= 1;
                                        break;
                                    } else {
                                        r.garbageEntities.push_back(player);
                                        garbageToSend.push_back(player);
                                        break;
                                    }
//                        std::cout << "player" << std::endl;//collision with player
                        //TODO: if health == 0, remove player from the game and pass isAlive to false
                        break;
                    }
                }
                for (auto &bullet: bulletVector) {
                    if (isColliding(
                        r.getComponent<GameEngine::Position>()[enemy].value().x,
                        r.getComponent<GameEngine::Position>()[enemy].value().y,
                        r.getComponent<GameEngine::Position>()[bullet].value().x,
                        r.getComponent<GameEngine::Position>()[bullet].value().y,
                        r.getComponent<GameEngine::Size>()[enemy].value().width,
                        r.getComponent<GameEngine::Size>()[enemy].value().height,
                        r.getComponent<GameEngine::Size>()[bullet].value().width,
                        r.getComponent<GameEngine::Size>()[bullet].value().height))
                    {
//                        r.getComponent<GameEngine::Position>()[enemy].value().x += 3000;
                        score += 5;
                        r.garbageEntities.push_back(enemy);
                        r.garbageEntities.push_back(bullet);
                        garbageToSend.push_back(enemy);
                        garbageToSend.push_back(bullet);
                        std::cout << "bullet" << std::endl;//collision with bullet
                        // TODO: change the pos of the enemy and not adding it to the garbage
                        break;
                    }
                }
            }
        }

        void collisionSystem(GameEngine::Registry &REGISTRY_DEFAULT_NAME, int &score)
        {
            EXTRACT_COMPONENT_CONST(GameEngine::Controllable, controllables);
            EXTRACT_COMPONENT_CONST(GameEngine::Position, positions);
            EXTRACT_COMPONENT_CONST(GameEngine::Hitbox, hitboxes);
            EXTRACT_COMPONENT_CONST(GameEngine::Size, sizes);
            EXTRACT_COMPONENT(GameEngine::Life, lives);
            EXTRACT_COMPONENT(GameEngine::Projectile, projectiles);
            std::vector<std::size_t> players;
            std::vector<std::size_t> enemies;

            for (std::size_t i = 0; i < controllables.size() && i < positions.size(); ++i) {
                if (std::find(r.garbageEntities.begin(), r.garbageEntities.end(), i) != r.garbageEntities.end())
                    continue;
                // Controllable - Continues if controllable is undefined or not controllable
                FROM_COMPONENT_TO_VARIABLE_CONST(controllables, i, controllable, hasControllable);
                if (!hasControllable || !controllable.value().isControllable)
                    continue;

                // Position - Continues if position is undefined
                FROM_COMPONENT_TO_VARIABLE_CONST(positions, i, _position, hasPosition);
                if (!hasPosition)
                    continue;

                // Life - Continues if life is undefined
                FROM_COMPONENT_TO_VARIABLE_CONST(lives, i, _life, hasLife);
                if (!hasLife)
                    continue;

                // Hitbox - Continues if hitbox is undefined
                FROM_COMPONENT_TO_VARIABLE_CONST(hitboxes, i, _hitbox, hasHitbox);
                if (!hasHitbox)
                    continue;

                players.push_back(i);
            }

            for (std::size_t e = 0; e < positions.size(); ++e) {
                if (std::find(r.garbageEntities.begin(), r.garbageEntities.end(), e) != r.garbageEntities.end())
                    continue;
                // Controllable - Continues if controllable is undefined or not controllable
                FROM_COMPONENT_TO_VARIABLE_CONST(controllables, e, controllable, hasControllable);
                if (hasControllable && controllable.value().isControllable)
                    continue;

                // Position - Continues if position is undefined
                FROM_COMPONENT_TO_VARIABLE_CONST(positions, e, _position, hasPosition);
                if (!hasPosition)
                    continue;

                // Life - Continues if life is undefined
                FROM_COMPONENT_TO_VARIABLE_CONST(lives, e, _life, hasLife);
                if (!hasLife)
                    continue;

                // Hitbox - Continues if hitbox is undefined
                FROM_COMPONENT_TO_VARIABLE_CONST(hitboxes, e, _hitbox, hasHitbox);
                if (!hasHitbox)
                    continue;

                // Projectile - Continues if projectile is undefined
                FROM_COMPONENT_TO_VARIABLE(projectiles, e, projectileComponent, hasProjectile);
                if (hasProjectile)
                    continue;

                enemies.push_back(e);
            }

            for (auto const &playerID : players) {
                // Player - Continues if player is undefined
                FROM_COMPONENT_TO_VARIABLE_CONST(positions, playerID, playerPosition, hasPlayerPosition);
                FROM_COMPONENT_TO_VARIABLE_CONST(sizes, playerID, playerSize, hasPlayerHitbox);
                FROM_COMPONENT_TO_VARIABLE(lives, playerID, playerLife, hasLife);
                if (!hasPlayerPosition || !hasPlayerHitbox || !hasLife)
                    continue;
                for (auto const &enemyID : enemies) {
                    for (std::size_t j = 0; j < positions.size(); ++j) {
                        if (std::find(r.garbageEntities.begin(), r.garbageEntities.end(), j) != r.garbageEntities.end())
                            continue;
                        if (playerID == j)
                            continue;
                        // Enemy, Player and Lives - Continues if one of these is undefined
                        FROM_COMPONENT_TO_VARIABLE_CONST(positions, enemyID, enemyPosition, hasEnemyPosition);
                        FROM_COMPONENT_TO_VARIABLE_CONST(sizes, enemyID, enemySize, hasEnemySize);
                        FROM_COMPONENT_TO_VARIABLE_CONST(hitboxes, enemyID, enemyHitbox, hasEnemyHitbox);
                        FROM_COMPONENT_TO_VARIABLE(projectiles, j, projectileComponent, hasProjectile);
                        FROM_COMPONENT_TO_VARIABLE(positions, j, projectilePosition, hasProjectilePosition);
                        FROM_COMPONENT_TO_VARIABLE(sizes, j, projectileSize, hasProjectileSize);
                        FROM_COMPONENT_TO_VARIABLE(hitboxes, j, projectileHitbox, hasProjectileHitbox);
                        if (!hasEnemyPosition || !hasEnemySize || !hasEnemyHitbox)
                            continue;
                        GameEngine::Life &life = playerLife.value();
                        if (isColliding(playerPosition.value().x, playerPosition.value().y, enemyPosition.value().x,
                                enemyPosition.value().y, playerSize.value().width, playerSize.value().height,
                                enemySize.value().width, enemySize.value().height)) {
                            if (life.life > 0) {
                                life.life -= 1;
                                break;
                            } else {
                                r.garbageEntities.push_back(std::size_t(playerID)); //
                                break;
                            }
                        }
                        if (hasProjectile && hasProjectilePosition && hasProjectileSize && hasProjectileHitbox) {
                            if (isColliding(enemyPosition.value().x, enemyPosition.value().y,
                                    projectilePosition.value().x, projectilePosition.value().y, enemySize.value().width,
                                    enemySize.value().height, projectileSize.value().width,
                                    projectileSize.value().height)) {
                                r.garbageEntities.push_back(std::size_t(enemyID));
                                r.garbageEntities.push_back(std::size_t(j));
                                score += 5;
                                break;
                            }
                        }
                    }
                }
            }
        }

        void attackSystem(GameEngine::Registry &REGISTRY_DEFAULT_NAME, std::vector<GameEngine::Entity> &entityVector)
        {
            auto &positions = r.getComponent<GameEngine::Position>();
            auto &controllables = r.getComponent<GameEngine::Controllable>();
            EXTRACT_COMPONENT(GameEngine::Size, sizes);
            bool isSpacePressedUnpressed = false;

            for (size_t i = 0; i < controllables.size(); ++i) {
                if (std::find(r.garbageEntities.begin(), r.garbageEntities.end(), i) != r.garbageEntities.end())
                    continue;
                FROM_COMPONENT_TO_VARIABLE(positions, i, positionComponent, _hasPosition);
                auto position = positions[i];
                FROM_COMPONENT_TO_VARIABLE(controllables, i, control, _hasControllable);
                FROM_COMPONENT_TO_VARIABLE(sizes, i, size, _hasSize)
                auto sizePlayer = sizes[i];

                if (_hasPosition && _hasControllable && control.value().isControllable) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isSpacePressedUnpressed) {
                        GameEngine::Entity bullet = r.spawnEntity();
                        r.addComponent<GameEngine::Size>(bullet, GameEngine::Size{10, 10});
                        r.addComponent<GameEngine::Position>(
                            bullet, GameEngine::Position{
                                        position.value().x, position.value().y + sizePlayer.value().height / 2});
                        r.addComponent<GameEngine::Velocity>(bullet, GameEngine::Velocity{25.0f, 0.0f});
                        r.addComponent<GameEngine::Hitbox>(bullet, GameEngine::Hitbox{});
                        r.addComponent<GameEngine::Drawable>(bullet, GameEngine::Drawable{true});
                        r.addComponent<GameEngine::Sprite>(
                            bullet, GameEngine::Sprite{"./../games/resources/R-Touhou/graphics/bullet.png",
                                        sf::Sprite(), sf::Texture()});
                        r.addComponent<GameEngine::ZIndex>(
                            bullet, GameEngine::ZIndex{GAME_ENGINE_Z_INDEX_VALUE_DEFAULT_VALUE - 1});
                        r.addComponent<GameEngine::Projectile>(bullet, GameEngine::Projectile{});
                        r.addComponent<GameEngine::Path>(
                            bullet, GameEngine::Path{position.value().x, position.value().y, 1920 + 50, 1080 + 50});
                        entityVector.push_back(bullet);
                    }
                }
                isSpacePressedUnpressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
            }
        }

        void deleteEntitiesSystem(GameEngine::Registry &REGISTRY_DEFAULT_NAME)
        {
            auto &positions = r.getComponent<Position>();
            auto &paths = r.getComponent<Path>();
            auto &projectiles = r.getComponent<Projectile>();

            for (size_t i = 0; i < positions.size(); ++i) {
                FROM_COMPONENT_TO_VARIABLE(positions, i, pos, _hasPosition);
                FROM_COMPONENT_TO_VARIABLE(paths, i, path, _hasPath);
                FROM_COMPONENT_TO_VARIABLE(projectiles, i, projectile, _hasProjectile);
                if (_hasPosition && _hasPath) {
                    if (_hasProjectile) {
                        if (pos.value().x >= path.value().endX || pos.value().y >= path.value().endY) {
                            if (std::find(r.garbageEntities.begin(), r.garbageEntities.end(), i) !=
                                r.garbageEntities.end())
                                continue;
                            auto entityId = r.getEntityById(i);
                            r.garbageEntities.push_back((std::size_t)entityId);
                            //
                        }
                    } else {
                        if (pos.value().x <= path.value().endX || pos.value().y <= path.value().endY) {
                            if (std::find(r.garbageEntities.begin(), r.garbageEntities.end(), i) !=
                                r.garbageEntities.end())
                                continue;
                            auto entityId = r.getEntityById(i);
                            r.garbageEntities.push_back((std::size_t)entityId);
                            //
                        }
                    }
                }
            }
        }

        void deleteEntitiesSystem(GameEngine::Registry &REGISTRY_DEFAULT_NAME, std::vector<int> &garbageToSend)
        {
            auto &positions = r.getComponent<Position>();
            auto &paths = r.getComponent<Path>();
            auto &projectiles = r.getComponent<Projectile>();

            for (size_t i = 0; i < positions.size(); ++i) {
                FROM_COMPONENT_TO_VARIABLE(positions, i, pos, _hasPosition);
                FROM_COMPONENT_TO_VARIABLE(paths, i, path, _hasPath);
                FROM_COMPONENT_TO_VARIABLE(projectiles, i, projectile, _hasProjectile);
                if (_hasPosition && _hasPath) {
                    if (_hasProjectile) {
                        if (pos.value().x >= path.value().endX || pos.value().y >= path.value().endY) {
                            if (std::find(r.garbageEntities.begin(), r.garbageEntities.end(), i) !=
                                r.garbageEntities.end())
                                continue;
                            auto entityId = r.getEntityById(i);
                            r.garbageEntities.push_back((std::size_t)entityId);
                            garbageToSend.push_back(i);
                        }
                    } else {
                        if (pos.value().x <= path.value().endX || pos.value().y <= path.value().endY) {
                            if (std::find(r.garbageEntities.begin(), r.garbageEntities.end(), i) !=
                                r.garbageEntities.end())
                                continue;
                            auto entityId = r.getEntityById(i);
                            r.getComponent<GameEngine::Position>()[entityId].value().x += 3000;
                        }
                    }
                }
            }
        }
    };
} // namespace GameEngine

#endif
