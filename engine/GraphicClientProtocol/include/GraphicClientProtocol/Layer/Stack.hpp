/*
** EPITECH PROJECT, 2023
** engine/GraphicClientProtocol/include/GraphicClientProtocol/Layer/Stack.hpp
** File description:
** -
*/

/// @file
/// @brief Stack of multiple Layers. It does not inherit from Layer

#pragma once
#include <vector>
#include "GraphicClientProtocol/Layer/Color.hpp"
#include "GraphicClientProtocol/Layer/Sprites.hpp"

namespace GraphicClientProtocol { namespace Layer {

enum class LayerType {
    UNKNOWN,
    COLOR,
    SPRITES,
};

using StackElementValue = struct StackElementValue_u {
    int unknown;
    GraphicClientProtocol::Layer::Color color;
    GraphicClientProtocol::Layer::Sprites sprites;
};

class StackElement
{

public:
    StackElement(void);
    StackElement(GraphicClientProtocol::Layer::Color layer);
    StackElement(GraphicClientProtocol::Layer::Sprites sprites);
public:
    void assignLayer(void);
    void assignLayer(GraphicClientProtocol::Layer::Color layer);
    void assignLayer(GraphicClientProtocol::Layer::Sprites sprites);
public:
    GraphicClientProtocol::Layer::StackElementValue value = {0, GraphicClientProtocol::Layer::Color(LType::Color())};
    GraphicClientProtocol::Layer::LayerType type = GraphicClientProtocol::Layer::LayerType::UNKNOWN;

};

using Stack = std::vector<GraphicClientProtocol::Layer::StackElement>;

}}
