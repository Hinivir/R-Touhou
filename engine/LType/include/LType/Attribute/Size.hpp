/*
** EPITECH PROJECT, 2023
** engine/LType/include/LType/Attribute/Size.hpp
** File description:
** -
*/

/// @file
/// @brief Defines the type used for xyz sizes

#pragma once
#include "LType/Attribute/GenericAxis3.hpp"

namespace LType { namespace Attribute {

/// @brief Type used for an axis of an Attribute::Size
using SizeAxis = float;

/// @brief Type used for simplified xyz LType::Attribute::Size
using SizeStruct = LType::Attribute::GenericAxis3Struct_s<LType::Attribute::SizeAxis>;

/// @brief Class used for xyz sizes
using Size = LType::Attribute::GenericAxis3<LType::Attribute::SizeAxis>;

}}
