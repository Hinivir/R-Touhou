/*
** EPITECH PROJECT, 2023
** engine/Game/include/AGame.hpp
** File description:
** -
*/

/// @file
/// @brief Default implemenation of AGame

#pragma once
#include "Game/IGame.hpp"

namespace Game {

class AGame : public Game::IGame
{
public:
    // << BASE >>

    // Init

    void init(void) override;

    // << PROCESS >>

    // Stacks

    Game::ProcessGraphicStack const &getProcessGraphicStack(void) const override;
    Game::ProcessPhysicsStack const &getProcessPhysicsStack(void) const override;

    // << ENGINE >>

    // Stacks

    /// @brief Amount of times the processPhysics should be called per seconds
    float getProcessPhysicsPerSec(void) const override;

protected:
    // << PROCESS >>

    // Stacks

    /// @brief Contains every processGraphic function
    Game::ProcessGraphicStack _processGraphicStack;
    /// @brief Contains every processPhysics function
    Game::ProcessPhysicsStack _processPhysicsStack;

    // << ENGINE >>

    // Stacks

    /// @brief Amount of times the processPhysics should be called per seconds
    float _processPhysicsPerSec = 10.0;
};

}
