/*
** EPITECH PROJECT, 2024
** L-Type-Game-RTouhou
** File description:
** SpriteTextureRect.hpp
*/

#ifndef L_TYPE_GAME_RTOUHOU_SPRITE_TEXTURE_RECT_HPP
#define L_TYPE_GAME_RTOUHOU_SPRITE_TEXTURE_RECT_HPP

#include "Components/RectBase.hpp"

namespace GameEngine
{
    using SpriteTextureRectValue = int;
    using SpriteTextureRect = GameEngine::RectBase<GameEngine::SpriteTextureRectValue, 'S'>;
}

#endif //L_TYPE_GAME_RTOUHOU_SPRITE_TEXTURE_RECT_HPP