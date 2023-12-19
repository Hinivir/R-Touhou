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

#define LTYPE_FUNCTION_PROCESS_GRAPHIC(FUNCTION_NAME, DELTA_NAME) void FUNCTION_NAME(LType::Delta const DELTA_NAME)
#define LTYPE_FUNCTION_PROCESS_PHYSICS(FUNCTION_NAME, DELTA_NAME) void FUNCTION_NAME(LType::Delta const DELTA_NAME)

namespace LType {

/// @brief Type representing a pointer to a processGraphic function
using ProcessGraphic = void (*)(LType::Delta const delta);
/// @brief Type representing a pointer to a processPhysics function
using ProcessPhysics = void (*)(LType::Delta const delta);

}
