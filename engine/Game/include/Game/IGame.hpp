/*
** EPITECH PROJECT, 2023
** engine/Game/include/IGame.hpp
** File description:
** -
*/

/// @file
/// @brief Interfaces for games

#pragma once
#include <vector>
#include "LType/Process.hpp"

namespace Game {

/// @brief List of multiple LType::ProcessGraphic elements
using ProcessGraphicStack = std::vector<LType::ProcessGraphic>;
/// @brief List of multiple LType::ProcessPhysics elements
using ProcessPhysicsStack = std::vector<LType::ProcessPhysics>;

class IGame
{
public:
    virtual ~IGame() = default;
public:
    // << BASE >>

    // Init

    /// @brief Initialization of the game
    virtual void init(void) = 0;

    // < PROCESS >

    // Stacks

    /// @brief
    virtual Game::ProcessGraphicStack const &getProcessGraphicStack(void) const = 0;
    /// @brief
    virtual Game::ProcessPhysicsStack const &getProcessPhysicsStack(void) const = 0;
};

}
