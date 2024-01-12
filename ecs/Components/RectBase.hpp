/*
** EPITECH PROJECT, 2024
** L-Type-Game-RTouhou
** File description:
** RectBase.hpp
*/

#ifndef L_TYPE_GAME_RTOUHOU_RECT_BASE_HPP
#define L_TYPE_GAME_RTOUHOU_RECT_BASE_HPP

#define GAME_ENGINE_RECT_BASE_DEFAULT_VALUE 0

namespace GameEngine
{
    template <typename T, char UNIQUE_ID>
    struct RectBase {
        T left = GAME_ENGINE_RECT_BASE_DEFAULT_VALUE;
        T top = GAME_ENGINE_RECT_BASE_DEFAULT_VALUE;
        T width = GAME_ENGINE_RECT_BASE_DEFAULT_VALUE;
        T height = GAME_ENGINE_RECT_BASE_DEFAULT_VALUE;
    };
}

#endif //L_TYPE_GAME_RTOUHOU_RECT_BASE_HPP