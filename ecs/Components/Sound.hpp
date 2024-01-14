/*
** EPITECH PROJECT, 2024
** L-Type-Game-RTouhou
** File description:
** Sound.hpp
*/

#ifndef L_TYPE_GAME_RTouhou_SOUND_HPP
#define L_TYPE_GAME_RTouhou_SOUND_HPP

#include <SFML/Audio/Music.hpp>

namespace GameEngine
{
    struct Sound
    {
        sf::Music music;
        std::string filePath;
        bool isLoaded = false;
    };
} // namespace GameEngine

#endif // L_TYPE_GAME_RTouhou_SOUND_HPP
