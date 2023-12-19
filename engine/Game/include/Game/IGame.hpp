/*
** EPITECH PROJECT, 2023
** engine/Game/include/IGame.hpp
** File description:
** -
*/

/// @file
/// @brief Interfaces for games

#pragma once
#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include "LType/Attribute/FilePath.hpp"
#include "LType/Attribute/Position.hpp"
#include "LType/Entity.hpp"
#include "LType/EntityInstance.hpp"
#include "LType/Process.hpp"

#define GAME_ENTITY LType::createEntityInstance<LType::Entity>()
#define GAME_ENTITY_TYPE(ENTITY_TYPE) LType::createEntityInstance<ENTITY_TYPE>()

namespace Game {

/// @brief List of multiple LType::EntityInstance elements
using EntityStack = std::vector<LType::EntityInstance>;

/// @brief Key of a AttributeStack
using AttributeStackKey = LType::EntityInstancePtr;
/// @brief List of attributes, mapping a pointer to the entity with the attribute's T value
template <typename T>
using AttributeStack = std::map<LType::EntityInstancePtr, T>;

/// @brief Structure containings all AttributeStacks
using AttributeStackStack = struct AttributeStackStack_s {
    Game::AttributeStack<LType::Attribute::Position> position;
    Game::AttributeStack<LType::Attribute::FilePath> spriteFilePath;
};

/// @brief List of multiple LType::ProcessGraphicStoraged elements
using ProcessGraphicStack = std::vector<LType::ProcessGraphicStoraged>;
/// @brief List of multiple LType::ProcessPhysicsStoraged elements
using ProcessPhysicsStack = std::vector<LType::ProcessPhysicsStoraged>;

class IGame
{
public:
    virtual ~IGame() = default;
public:
    // << BASE >>

    // Init

    /// @brief Initialization of the game
    virtual void init(void) = 0;

    // << STACKS >>

    // Process

    /// @brief Adds a function point to the ProcessGraphicStack
    /// @param target Source of the pointer. Can be set to `LType::FunctionTarget()` instead
    /// @param function Pointer to the function to add
    virtual void addFunctionProcessGraphic(LType::FunctionTarget const target, LType::ProcessGraphic function) = 0;
    /// @brief Adds a function point to the ProcessPhysicsStack
    /// @param target Source of the pointer. Can be set to `LType::FunctionTarget()` instead
    /// @param function Pointer to the function to add
    virtual void addFunctionProcessPhysics(LType::FunctionTarget const target, LType::ProcessPhysics function) = 0;
    /// @return A constant reference of `_processGraphicStack`
    virtual Game::ProcessGraphicStack const &getProcessGraphicStack(void) const = 0;
    /// @return A constant reference of `_processPhysicsStack`
    virtual Game::ProcessPhysicsStack const &getProcessPhysicsStack(void) const = 0;

    // Entity

    /// @brief Adds an entity locally
    /// @param entity Reference to an `EntityInstance`
    /// @return Copy of the refence to the `EntityInstance`
    virtual LType::EntityInstance addEntity(LType::EntityInstance entity) = 0;

    // << ENGINE >>

    /// @brief
    virtual float getProcessPhysicsPerSec(void) const = 0;
};

}
