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
#include "LType/InputList.hpp"

namespace Game {

class AGame : public Game::IGame
{
public:
    // << BASE >>

    // Init

    /// @brief Initialization of the game
    void init(void) override;

    // << INPUTS >>

    /// @brief Refreshs every input based on the content of `inputMapWindow`
    /// @param inputMapWindow (Input::InputMapWindow const &) (optional) Reference to a source input map
    void refreshInputs(void) override;
    /// @brief Refreshs every input based on the content of `inputMapWindow`
    /// @param inputMapWindow (Input::InputMapWindow const &) (optional) Reference to a source input map
    void refreshInputs(Input::InputMapWindow const &inputMapWindow) override;

    /// @brief Checks if an input is being currently pressed
    /// @param input (LType::InputList const)
    /// @return `True` or `False`
    bool isInputPressed(LType::InputList const input) override;
    /// @brief Checks if an input has just been pressed
    /// @param input (LType::InputList const)
    /// @return `True` or `False`
    bool hasInputJustBeenPressed(LType::InputList const input) override;

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
    /// @return A constant reference of `_entityStack`
    Game::EntityStack const &getEntityStack(void) const override;
    /// @return A constant reference of `_entityStackNew`
    Game::EntityPtrStack const &getEntityStackNew(void) const;
    /// @brief Empties `_entityStackNew`
    void clearEntityStackNew(void);

    // << ENGINE >>

    // Stacks

    /// @brief Amount of times the processPhysics should be called per seconds
    float getProcessPhysicsPerSec(void) const override;

protected:
    // << INPUTS >>

    /// @brief List containing information about if inputs are pressed
    bool _inputsPressed[static_cast<std::size_t>(LType::InputList::TOTAL)];
    /// @brief List containing information about if inputs have just been pressed
    bool _inputsJustPressed[static_cast<std::size_t>(LType::InputList::TOTAL)];

    /// @brief Length of `_inputsPressed` and `_inputsJustPressed`
    std::size_t _inputsLength = static_cast<std::size_t>(LType::InputList::TOTAL);

    // << STACKS >>

    // Process

    /// @brief Contains every processGraphic function
    Game::ProcessGraphicStack _processGraphicStack;
    /// @brief Contains every processPhysics function
    Game::ProcessPhysicsStack _processPhysicsStack;

    // Entity

    /// @brief Contains entities added to the game
    Game::EntityStack _entityStack;
    /// @brief Contains entities added to the game and still not treated by the engine
    Game::EntityPtrStack _entityStackNew;

    // << ENGINE >>

    // Stacks

    /// @brief Amount of times the processPhysics should be called per seconds
    float _processPhysicsPerSec = 30.0;
};

}
