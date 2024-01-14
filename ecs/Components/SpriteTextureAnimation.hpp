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
    /// @brief Defines which frame a SpriteTextureAnimation should use
    using SpriteTextureAnimationSlicing =
        GameEngine::Position2BaseDefault1<GameEngine::SpriteTextureAnimationSlicingValue, 's'>;

    using SpriteTextureAnimationFrameValue = int;
    /// @brief Defines how a SpriteTextureAnimation should slice a texture
    using SpriteTextureAnimationFrame = GameEngine::Position2Base<GameEngine::SpriteTextureAnimationFrameValue, 'f'>;

    /// @brief Defines the slicing of a sprite's texture for animating
    /// @note When combined with SpriteTextureRect, the slicing is applied AFTER the texture rect
    struct SpriteTextureAnimation
    {
        /// @brief Defines how the texture is sliced
        /// @example A slicing of {2, 2} will result in 4 different frames
        GameEngine::SpriteTextureAnimationSlicing slicing;
        /// @brief Defines which frame should be used
        /// @example The frame {0, 0}, the default value, corresponds to the first frame (top-left)
        GameEngine::SpriteTextureAnimationFrame frame;
    };
} // namespace GameEngine

#endif /* !SPRITE_TEXTURE_ANIMATION_HPP_ */
