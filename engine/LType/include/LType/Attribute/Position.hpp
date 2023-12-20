/*
** EPITECH PROJECT, 2023
** engine/LType/include/LType/Attribute/Position.hpp
** File description:
** -
*/

/// @file
/// @brief Defines the type used for xyz positions

#pragma once
#include <iostream>

namespace LType { namespace Attribute {

/// @brief Type used for an axis of an Attribute::Position
using PositionAxis = float;
/// @brief Type used for simplified xyz Attribute::Position
using PositionStruct = struct PositionSimplifiedPositionStruct_s {
    LType::Attribute::PositionAxis x;
    LType::Attribute::PositionAxis y;
    LType::Attribute::PositionAxis z;
};
/// @brief Class used for xyz positions
class Position
{
public:
    Position(void) {};
    Position(LType::Attribute::PositionAxis const x, LType::Attribute::PositionAxis const y) : x(x), y(y) {};
    Position(LType::Attribute::PositionAxis const x, LType::Attribute::PositionAxis const y, LType::Attribute::PositionAxis const z) : x(x), y(y), z(z) {};
    Position(LType::Attribute::PositionStruct const xyz) : x(xyz.x), y(xyz.y), z(xyz.z) {};
public:
    LType::Attribute::PositionAxis x = 0.0;
    LType::Attribute::PositionAxis y = 0.0;
    LType::Attribute::PositionAxis z = 0.0;
};

}}
