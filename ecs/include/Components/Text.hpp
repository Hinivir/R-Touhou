/*
** EPITECH PROJECT, 2024
** L-Type-Game-RTouhou
** File description:
** Text.hpp
*/

#ifndef L_TYPE_GAME_RTouhou_TEXT_HPP
#define L_TYPE_GAME_RTouhou_TEXT_HPP

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics.hpp>

namespace GameEngine
{
    struct Text {
        std::string path;
        sf::Text Text;
        sf::Texture texture;
    };
}

#endif //L_TYPE_GAME_RTouhou_TEXT_HPP
