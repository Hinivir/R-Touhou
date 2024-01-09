/*
** EPITECH PROJECT, 2024
** L-Type-Game-RTouhou
** File description:
** Rect.hpp
*/

#ifndef L_TYPE_GAME_RTOUHOU_RECT_HPP
#define L_TYPE_GAME_RTOUHOU_RECT_HPP

#define GAME_ENGINE_RECT_DEFAULT_VALUE 0

namespace GameEngine
{
    template <typename T>
    struct Rect {
        T left = GAME_ENGINE_COLOR_VALUE_DEFAULT_VALUE;
        T top = GAME_ENGINE_COLOR_VALUE_DEFAULT_VALUE;
        T width = GAME_ENGINE_COLOR_VALUE_DEFAULT_VALUE;
        T height = GAME_ENGINE_COLOR_VALUE_DEFAULT_VALUE;
    };
}

#endif //L_TYPE_GAME_RTOUHOU_RECT_HPP