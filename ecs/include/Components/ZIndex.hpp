/*
** EPITECH PROJECT, 2024
** R-Touhou_Bootstrap
** File description:
** Position
*/

#ifndef ZINDEX_HPP_
#define ZINDEX_HPP_

#define GAME_ENGINE_Z_INDEX_VALUE_LOWEST_VALUE 0
#define GAME_ENGINE_Z_INDEX_VALUE_DEFAULT_VALUE 1000

namespace GameEngine
{
    using ZIndexValue = unsigned int;
    struct ZIndex
    {
        GameEngine::ZIndexValue zIndex = GAME_ENGINE_Z_INDEX_VALUE_DEFAULT_VALUE;
    };
} // namespace GameEngine

#endif /* !ZINDEX_HPP_ */
