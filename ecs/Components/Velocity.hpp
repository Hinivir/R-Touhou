/*
** EPITECH PROJECT, 2024
** R-Touhou_Bootstrap
** File description:
** Velocity
*/

#ifndef VELOCITY_HPP_
#define VELOCITY_HPP_

#include "Components/Position2Base.hpp"

namespace GameEngine
{
    using VelocityValue = float;
    using Velocity = GameEngine::Position2Base<GameEngine::VelocityValue, 'V'>;
} // namespace GameEngine

#endif /* !VELOCITY_HPP_ */
