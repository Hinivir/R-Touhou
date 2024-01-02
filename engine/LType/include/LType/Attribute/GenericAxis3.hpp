/*
** EPITECH PROJECT, 2023
** engine/LType/include/LType/Attribute/GenericAxis3.hpp
** File description:
** -
*/

/// @file
/// @brief Defines the type used for any type of xyz based attribute

#pragma once

namespace LType { namespace Attribute {

/// @brief Struct used for simplified xyz LType::Attribute::GenericAxis3
template <typename T>
struct GenericAxis3Struct_s {
    T x;
    T y;
    T z;
};

/// @brief Class used for xyz positions
template <typename T>
class GenericAxis3
{
public:
    GenericAxis3(void) {};
    GenericAxis3(T const x, T const y) : x(x), y(y) {};
    GenericAxis3(T const x, T const y, T const z) : x(x), y(y), z(z) {};
    GenericAxis3(LType::Attribute::GenericAxis3Struct_s<T> const xyz) : x(xyz.x), y(xyz.y), z(xyz.z) {};
public:
    T x = 0.0;
    T y = 0.0;
    T z = 0.0;
};

}}
