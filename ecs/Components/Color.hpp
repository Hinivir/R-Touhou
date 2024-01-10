/*
** EPITECH PROJECT, 2024
** L-Type-Game-RTouhou
** File description:
** Color.hpp
*/

#ifndef L_TYPE_GAME_RTOUHOU_COLOR_HPP
#define L_TYPE_GAME_RTOUHOU_COLOR_HPP

#define GAME_ENGINE_COLOR_VALUE_MIN_VALUE 0
#define GAME_ENGINE_COLOR_VALUE_DEFAULT_VALUE 255
#define GAME_ENGINE_COLOR_VALUE_MAX_VALUE 255

namespace GameEngine
{
    using ColorValue = unsigned char;
    struct Color {
        GameEngine::ColorValue r = GAME_ENGINE_COLOR_VALUE_DEFAULT_VALUE;
        GameEngine::ColorValue g = GAME_ENGINE_COLOR_VALUE_DEFAULT_VALUE;
        GameEngine::ColorValue b = GAME_ENGINE_COLOR_VALUE_DEFAULT_VALUE;
        GameEngine::ColorValue a = GAME_ENGINE_COLOR_VALUE_DEFAULT_VALUE;
    };
}

#endif //L_TYPE_GAME_RTOUHOU_COLOR_HPP