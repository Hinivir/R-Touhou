/*
** EPITECH PROJECT, 2023
** engine/GraphicClientProtocol/include/GraphicClientProtocol/Layer/Base.hpp
** File description:
** -
*/

/// @file
/// @brief Layer of just one color

#pragma once
#include "GraphicClientProtocol/Color.hpp"
#include "GraphicClientProtocol/Layer/Base.hpp"

namespace GraphicClientProtocol { namespace Layer {

class Color : public GraphicClientProtocol::Layer::Base {

public:
    Color(GraphicClientProtocol::Color const &color);
    Color(GraphicClientProtocol::Layer::Color const &other);

public:
    GraphicClientProtocol::Color color;

};

}}
