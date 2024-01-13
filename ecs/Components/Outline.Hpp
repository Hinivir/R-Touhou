/*
** EPITECH PROJECT, 2024
** L-Type-Game-RTouhou
** File description:
** Outline.hpp
*/

#ifndef L_TYPE_GAME_RTOUHOU_OUTLINE_HPP
#define L_TYPE_GAME_RTOUHOU_OUTLINE_HPP

#define GAME_ENGINE_OUTLINE_COLOR_DEFAULT GameEngine::Color{0, 0, 0, 255};
#define GAME_ENGINE_OUTLINE_THICKNESS_DEFAULT 0

#include "Components/Color.hpp"

namespace GameEngine
{
    using OutlineColorValue = GameEngine::Color;
    using OutlineThicknessValue = int;
    struct Outline {
        GameEngine::OutlineThicknessValue thickness = GAME_ENGINE_OUTLINE_THICKNESS_DEFAULT;
        GameEngine::OutlineColorValue color = GAME_ENGINE_OUTLINE_COLOR_DEFAULT;
    };
}

#endif //L_TYPE_GAME_RTOUHOU_OUTLINE_HPP