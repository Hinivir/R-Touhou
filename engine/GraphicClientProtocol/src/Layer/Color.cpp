/*
** EPITECH PROJECT, 2023
** engine/GraphicClientProtocol/src/Layer/Color.cpp
** File description:
** -
*/

#include "GraphicClientProtocol/Layer/Color.hpp"

GraphicClientProtocol::Layer::Color::Color(LType::Color const &color) :
    color(color)
{ }

GraphicClientProtocol::Layer::Color::Color(GraphicClientProtocol::Layer::Color const &other) :
    color(other.color)
{ }
