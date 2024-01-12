/*
** EPITECH PROJECT, 2024
** R-Touhou_Bootstrap
** File description:
** Position
*/

#ifndef POSITION_HPP_
#define POSITION_HPP_

#include "Components/Position2Base.hpp"

namespace GameEngine
{
    using PositionValue = float;
    using Position = GameEngine::Position2Base<GameEngine::PositionValue, 'P'>;
} // namespace GameEngine

#endif /* !POSITION_HPP_ */
