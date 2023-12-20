/*
** EPITECH PROJECT, 2023
** engine/LType/include/LType/Process.hpp
** File description:
** -
*/

/// @file
/// @brief Defines types for process functions

#pragma once
#include "LType/Delta.hpp"
#include "LType/EntityInstance.hpp"

#define LTYPE_FUNCTION(FUNCTION_NAME, TARGET_NAME) \
    void FUNCTION_NAME(LType::GameRefenrence _game, LType::GameRefenrence game, LType::FunctionTargetPtr const TARGET_NAME)
#define LTYPE_FUNCTION_PROCESS_GRAPHIC(FUNCTION_NAME, TARGET_NAME, DELTA_NAME) \
    void FUNCTION_NAME(LType::GameRefenrence _game, LType::FunctionTargetPtr const TARGET_NAME, LType::Delta const DELTA_NAME)
#define LTYPE_FUNCTION_PROCESS_PHYSICS(FUNCTION_NAME, TARGET_NAME, DELTA_NAME) \
    void FUNCTION_NAME(LType::GameRefenrence _game, LType::FunctionTargetPtr const TARGET_NAME, LType::Delta const DELTA_NAME)

namespace Game { class IGame; }

namespace LType {

using GameRefenrence = Game::IGame &;

/// @brief Type representing a reference to an element used by a function
using FunctionTarget = LType::EntityInstancePtr;
/// @brief Type representing a pointed to an element used by a function
using FunctionTargetPtr = LType::EntityInstance;

/// @brief Type representing a pointer to a processGraphic function
using ProcessGraphic = void (*)(LType::GameRefenrence game, LType::FunctionTargetPtr target, LType::Delta const delta);
/// @brief Type representing a pointer to a processPhysics function
using ProcessPhysics = void (*)(LType::GameRefenrence game, LType::FunctionTargetPtr target, LType::Delta const delta);

/// @brief Structure representing a ProcessGraphic and its related content
using ProcessGraphicStoraged = struct ProcessGraphicStoraged_s {
    LType::FunctionTarget target;
    LType::ProcessGraphic function;
};
/// @brief Structure representing a ProcessPhysics and its related content
using ProcessPhysicsStoraged = struct ProcessPhysicsStoraged_s {
    LType::FunctionTarget target;
    LType::ProcessPhysics function;
};

}
