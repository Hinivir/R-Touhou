/*
** EPITECH PROJECT, 2023
** engine/GraphicClientProtocol/include/GraphicClientProtocol/Color.hpp
** File description:
** -
*/

#pragma once

#define GCP_COLOR_VALUE GraphicClientProtocol::ColorValue

namespace GraphicClientProtocol {

using ColorValue = float;

class Color {

public:
    Color(void);
    Color(GCP_COLOR_VALUE const r, GCP_COLOR_VALUE const g, GCP_COLOR_VALUE const b);
    Color(GCP_COLOR_VALUE const r, GCP_COLOR_VALUE const g, GCP_COLOR_VALUE const b, GCP_COLOR_VALUE const a);
    Color(GraphicClientProtocol::Color const &color);
public:
    // Equal
    void operator=(GraphicClientProtocol::Color const &color);
    void operator*=(GraphicClientProtocol::Color const &color);
    void operator/=(GraphicClientProtocol::Color const &color);
    // Booleans
    bool operator==(GraphicClientProtocol::Color const &color) const;
    bool operator!=(GraphicClientProtocol::Color const &color) const;
    // Operators
    GraphicClientProtocol::Color operator*(GraphicClientProtocol::Color const &color) const;
    GraphicClientProtocol::Color operator/(GraphicClientProtocol::Color const &color) const;
public:
    /// @brief Red
    GraphicClientProtocol::ColorValue r = 1.0;
    /// @brief Green
    GraphicClientProtocol::ColorValue g = 1.0;
    /// @brief Blue
    GraphicClientProtocol::ColorValue b = 1.0;
    /// @brief Alpha (opposite of transparency)
    GraphicClientProtocol::ColorValue a = 1.0;

};

}
