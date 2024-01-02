/*
** EPITECH PROJECT, 2023
** engine/LType/include/LType/Attribute/Position.hpp
** File description:
** -
*/

/// @file
/// @brief Defines the type used for xyz positions

#pragma once
#include "LType/Attribute/GenericAxis3.hpp"

namespace LType { namespace Attribute {

/// @brief Type used for an axis of an Attribute::Position
using PositionAxis = float;

/// @brief Type used for simplified xyz LType::Attribute::Position
using PositionStruct = LType::Attribute::GenericAxis3Struct_s<LType::Attribute::PositionAxis>;

/// @brief Class used for xyz positions
using Position = LType::Attribute::GenericAxis3<LType::Attribute::PositionAxis>;

}}
