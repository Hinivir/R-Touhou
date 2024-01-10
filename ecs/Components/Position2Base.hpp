/*
** EPITECH PROJECT, 2024
** L-Type-Game-RTouhou
** File description:
** Position2Base.hpp
*/

#ifndef L_TYPE_GAME_RTOUHOU_POSITION_2_BASE_HPP
#define L_TYPE_GAME_RTOUHOU_POSITION_2_BASE_HPP

#define GAME_ENGINE_POSITION_2_BASE_DEFAULT_VALUE 0
#define GAME_ENGINE_POSITION_2_BASE_DEFAULT_VALUE_1 1

namespace GameEngine
{
    template <typename T, char UNIQUE_ID>
    struct Position2Base {
        T x = GAME_ENGINE_POSITION_2_BASE_DEFAULT_VALUE;
        T y = GAME_ENGINE_POSITION_2_BASE_DEFAULT_VALUE;
    };

    template <typename T, char UNIQUE_ID>
    struct Position2BaseDefault1 {
        T x = GAME_ENGINE_POSITION_2_BASE_DEFAULT_VALUE_1;
        T y = GAME_ENGINE_POSITION_2_BASE_DEFAULT_VALUE_1;
    };
}

#endif //L_TYPE_GAME_RTOUHOU_POSITION_2_BASE_HPP