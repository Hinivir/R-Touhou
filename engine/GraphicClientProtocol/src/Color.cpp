/*
** EPITECH PROJECT, 2023
** engine/GraphicClientProtocol/src/Color.cpp
** File description:
** -
*/

#include "GraphicClientProtocol/Color.hpp"

GraphicClientProtocol::Color::Color(void)
{ }

GraphicClientProtocol::Color::Color(GCP_COLOR_VALUE const r, GCP_COLOR_VALUE const g, GCP_COLOR_VALUE const b) :
    r(r), g(g), b(b)
{ }

GraphicClientProtocol::Color::Color(GCP_COLOR_VALUE const r, GCP_COLOR_VALUE const g, GCP_COLOR_VALUE const b, GCP_COLOR_VALUE const a) :
    r(r), g(g), b(b), a(a)
{ }

GraphicClientProtocol::Color::Color(GraphicClientProtocol::Color const &color) :
    r(color.r), g(color.g), b(color.b), a(color.a)
{ }

// Equal

void GraphicClientProtocol::Color::operator=(GraphicClientProtocol::Color const &color)
{
    r = color.r;
    g = color.g;
    b = color.b;
    a = color.a;
}

void GraphicClientProtocol::Color::operator*=(GraphicClientProtocol::Color const &color)
{
    r *= color.r;
    g *= color.g;
    b *= color.b;
    a *= color.a;
}

void GraphicClientProtocol::Color::operator/=(GraphicClientProtocol::Color const &color)
{
    r /= color.r;
    g /= color.g;
    b /= color.b;
    a /= color.a;
}

// Booleans

bool GraphicClientProtocol::Color::operator==(GraphicClientProtocol::Color const &color) const
{
    return (r == color.r && g == color.g && b == color.b && a == color.a);
}

bool GraphicClientProtocol::Color::operator!=(GraphicClientProtocol::Color const &color) const
{
    return (r != color.r && g != color.g && b != color.b && a != color.a);
}

// Operators

GraphicClientProtocol::Color GraphicClientProtocol::Color::operator*(GraphicClientProtocol::Color const &color) const
{
    return GraphicClientProtocol::Color(r * color.r, g * color.g, b * color.b, a * color.a);
}

GraphicClientProtocol::Color GraphicClientProtocol::Color::operator/(GraphicClientProtocol::Color const &color) const
{
    return GraphicClientProtocol::Color(r / color.r, g / color.g, b / color.b, a / color.a);
}
