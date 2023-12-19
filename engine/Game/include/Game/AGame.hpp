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

    // < PROCESS >

    // Stacks

    Game::ProcessGraphicStack const &getProcessGraphicStack(void) const override;
    Game::ProcessPhysicsStack const &getProcessPhysicsStack(void) const override;
public:
    /// @brief Contains every processGraphic function
    Game::ProcessGraphicStack _processGraphicStack;
    /// @brief Contains every processPhysics function
    Game::ProcessPhysicsStack _processPhysicsStack;
};

}
