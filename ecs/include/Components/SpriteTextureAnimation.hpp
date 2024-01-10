/*
** EPITECH PROJECT, 2024
** R-Touhou_Bootstrap
** File description:
** SpriteTextureAnimation
*/

#ifndef SPRITE_TEXTURE_ANIMATION_HPP_
#define SPRITE_TEXTURE_ANIMATION_HPP_

#include <cstddef>
#include "Position2Base.hpp"

namespace GameEngine
{
    using SpriteTextureAnimationSlicingValue = int;
    using SpriteTextureAnimationSlicing = GameEngine::Position2BaseDefault1<GameEngine::SpriteTextureAnimationSlicingValue, 's'>;

    using SpriteTextureAnimationFrameValue = int;
    using SpriteTextureAnimationFrame = GameEngine::Position2Base<GameEngine::SpriteTextureAnimationFrameValue, 'f'>;

    struct SpriteTextureAnimation {
        GameEngine::SpriteTextureAnimationSlicing slicing;
        GameEngine::SpriteTextureAnimationFrame frame;
    };
} // namespace GameEngine

#endif /* !SPRITE_TEXTURE_ANIMATION_HPP_ */
