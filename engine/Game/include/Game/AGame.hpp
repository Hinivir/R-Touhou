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

    /// @brief Initialization of the game
    void init(void) override;

    // << STACKS >>

    // Process

    /// @brief Adds a function point to the ProcessGraphicStack
    /// @param target Source of the pointer. Can be set to `LType::FunctionTarget()` instead
    /// @param function Pointer to the function to add
    void addFunctionProcessGraphic(LType::FunctionTarget const target, LType::ProcessGraphic function) override;
    /// @brief Adds a function point to the ProcessPhysicsStack
    /// @param target Source of the pointer. Can be set to `LType::FunctionTarget()` instead
    /// @param function Pointer to the function to add
    void addFunctionProcessPhysics(LType::FunctionTarget const target, LType::ProcessPhysics function) override;
    /// @return A constant reference of `_processGraphicStack`
    Game::ProcessGraphicStack const &getProcessGraphicStack(void) const override;
    /// @return A constant reference of `_processPhysicsStack`
    Game::ProcessPhysicsStack const &getProcessPhysicsStack(void) const override;

    // Entity

    /// @brief Adds an entity locally
    /// @param entity Reference to an `EntityInstance`
    /// @return Copy of the refence to the `EntityInstance`
    LType::EntityInstance addEntity(LType::EntityInstance entity) override;

    // << ENGINE >>

    // Stacks

    /// @brief Amount of times the processPhysics should be called per seconds
    float getProcessPhysicsPerSec(void) const override;

protected:
    // << STACKS >>

    // Process

    /// @brief Contains every processGraphic function
    Game::ProcessGraphicStack _processGraphicStack;
    /// @brief Contains every processPhysics function
    Game::ProcessPhysicsStack _processPhysicsStack;

    // Entity

    /// @brief Contains entities added to the game
    Game::EntityStack _entityStack;

    // << ENGINE >>

    // Stacks

    /// @brief Amount of times the processPhysics should be called per seconds
    float _processPhysicsPerSec = 10.0;
};

}
