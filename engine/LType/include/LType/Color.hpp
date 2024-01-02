/*
** EPITECH PROJECT, 2023
** engine/LType/include/LType/Color.hpp
** File description:
** -
*/

#pragma once

#define GCP_COLOR_VALUE LType::ColorValue

namespace LType {

using ColorValue = float;

class Color {

public:
    Color(void);
    Color(GCP_COLOR_VALUE const r, GCP_COLOR_VALUE const g, GCP_COLOR_VALUE const b);
    Color(GCP_COLOR_VALUE const r, GCP_COLOR_VALUE const g, GCP_COLOR_VALUE const b, GCP_COLOR_VALUE const a);
    Color(LType::Color const &color);
public:
    // Equal
    void operator=(LType::Color const &color);
    void operator*=(LType::Color const &color);
    void operator/=(LType::Color const &color);
    // Booleans
    bool operator==(LType::Color const &color) const;
    bool operator!=(LType::Color const &color) const;
    // Operators
    LType::Color operator*(LType::Color const &color) const;
    LType::Color operator/(LType::Color const &color) const;
public:
    /// @brief Red
    LType::ColorValue r = 1.0;
    /// @brief Green
    LType::ColorValue g = 1.0;
    /// @brief Blue
    LType::ColorValue b = 1.0;
    /// @brief Alpha (opposite of transparency)
    LType::ColorValue a = 1.0;

};

}
