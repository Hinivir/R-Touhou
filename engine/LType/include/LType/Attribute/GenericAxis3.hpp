/*
** EPITECH PROJECT, 2023
** engine/LType/include/LType/Attribute/GenericAxis3.hpp
** File description:
** -
*/

/// @file
/// @brief Defines the type used for any type of xyz based attribute

#pragma once

#define LTYPE_ATTRIBUTE_GENERICAXIS3_EQUAL_OPERATOR(FUNCTION, OPERATOR) void FUNCTION(LType::Attribute::GenericAxis3<T> const &other) { x OPERATOR other.x; }
#define LTYPE_ATTRIBUTE_GENERICAXIS3_SIMPLE_OPERATOR(FUNCTION, OPERATOR) LType::Attribute::GenericAxis3<T> FUNCTION(LType::Attribute::GenericAxis3<T> const &other) const { return LType::Attribute::GenericAxis3<T>(x OPERATOR other.x, y OPERATOR other.y, z OPERATOR other.z); }

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
    GenericAxis3(T const x, T const y, T const z) : x(x), y(y), z(z) {};
    GenericAxis3(LType::Attribute::GenericAxis3Struct_s<T> const xyz) : x(xyz.x), y(xyz.y), z(xyz.z) {};
public:
    LTYPE_ATTRIBUTE_GENERICAXIS3_EQUAL_OPERATOR(operator=, =);
    LTYPE_ATTRIBUTE_GENERICAXIS3_EQUAL_OPERATOR(operator+=, +=);
    LTYPE_ATTRIBUTE_GENERICAXIS3_EQUAL_OPERATOR(operator-=, -=);
    LTYPE_ATTRIBUTE_GENERICAXIS3_EQUAL_OPERATOR(operator*=, *=);
    LTYPE_ATTRIBUTE_GENERICAXIS3_EQUAL_OPERATOR(operator/=, /=);
    LTYPE_ATTRIBUTE_GENERICAXIS3_EQUAL_OPERATOR(operator%=, %=);
    void operator==(LType::Attribute::GenericAxis3<T> const &other) { return (x == other.x && y == other.y && z == other.z); };
    void operator!=(LType::Attribute::GenericAxis3<T> const &other) { return (x != other.x || y != other.y || z != other.z); };
    LTYPE_ATTRIBUTE_GENERICAXIS3_SIMPLE_OPERATOR(operator+, +);
    LTYPE_ATTRIBUTE_GENERICAXIS3_SIMPLE_OPERATOR(operator-, -);
    LTYPE_ATTRIBUTE_GENERICAXIS3_SIMPLE_OPERATOR(operator*, *);
    LTYPE_ATTRIBUTE_GENERICAXIS3_SIMPLE_OPERATOR(operator/, /);
    LTYPE_ATTRIBUTE_GENERICAXIS3_SIMPLE_OPERATOR(operator%, %);
public:
    T x;
    T y;
    T z;
};

}}
