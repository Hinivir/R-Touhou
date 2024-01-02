/*
** EPITECH PROJECT, 2023
** engine/LType/src/Color.cpp
** File description:
** -
*/

#include "LType/Color.hpp"

LType::Color::Color(void)
{ }

LType::Color::Color(GCP_COLOR_VALUE const r, GCP_COLOR_VALUE const g, GCP_COLOR_VALUE const b) :
    r(r), g(g), b(b)
{ }

LType::Color::Color(GCP_COLOR_VALUE const r, GCP_COLOR_VALUE const g, GCP_COLOR_VALUE const b, GCP_COLOR_VALUE const a) :
    r(r), g(g), b(b), a(a)
{ }

LType::Color::Color(LType::Color const &color) :
    r(color.r), g(color.g), b(color.b), a(color.a)
{ }

// Equal

void LType::Color::operator=(LType::Color const &color)
{
    r = color.r;
    g = color.g;
    b = color.b;
    a = color.a;
}

void LType::Color::operator*=(LType::Color const &color)
{
    r *= color.r;
    g *= color.g;
    b *= color.b;
    a *= color.a;
}

void LType::Color::operator/=(LType::Color const &color)
{
    r /= color.r;
    g /= color.g;
    b /= color.b;
    a /= color.a;
}

// Booleans

bool LType::Color::operator==(LType::Color const &color) const
{
    return (r == color.r && g == color.g && b == color.b && a == color.a);
}

bool LType::Color::operator!=(LType::Color const &color) const
{
    return (r != color.r && g != color.g && b != color.b && a != color.a);
}

// Operators

LType::Color LType::Color::operator*(LType::Color const &color) const
{
    return LType::Color(r * color.r, g * color.g, b * color.b, a * color.a);
}

LType::Color LType::Color::operator/(LType::Color const &color) const
{
    return LType::Color(r / color.r, g / color.g, b / color.b, a / color.a);
}
