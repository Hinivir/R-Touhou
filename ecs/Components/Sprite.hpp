/*
** EPITECH PROJECT, 2024
** L-Type-Game-RTouhou
** File description:
** Sprite.hpp
*/

#ifndef L_TYPE_GAME_RTouhou_SPRITE_HPP
#define L_TYPE_GAME_RTouhou_SPRITE_HPP

#include <SFML/Graphics.hpp>

namespace GameEngine
{
    struct Sprite {
        std::string path;
        sf::Sprite sprite;
        sf::Texture texture;
    };
}

#endif //L_TYPE_GAME_RTouhou_SPRITE_HPP
