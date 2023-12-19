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

#define LTYPE_FUNCTION_PROCESS_GRAPHIC(FUNCTION_NAME, DELTA_NAME, TARGET_NAME) void FUNCTION_NAME(LType::Delta const DELTA_NAME, LType::ProcessGraphicTarget const TARGET_NAME)
#define LTYPE_FUNCTION_PROCESS_PHYSICS(FUNCTION_NAME, DELTA_NAME, TARGET_NAME) void FUNCTION_NAME(LType::Delta const DELTA_NAME, LType::ProcessPhysicsTarget const TARGET_NAME)

namespace LType {

/// @brief Type representing a pointer to an element used by a ProcessGraphic
using ProcessGraphicTarget = void *;
/// @brief Type representing a pointer to an element used by a processPhysics
using ProcessPhysicsTarget = void *;

/// @brief Type representing a pointer to a processGraphic function
using ProcessGraphic = void (*)(LType::Delta const delta, LType::ProcessGraphicTarget target);
/// @brief Type representing a pointer to a processPhysics function
using ProcessPhysics = void (*)(LType::Delta const delta, LType::ProcessPhysicsTarget target);

}
