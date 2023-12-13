/*
** EPITECH PROJECT, 2023
** engine/GraphicClientProtocol/src/Layer/Stack.cpp
** File description:
** -
*/

#include "GraphicClientProtocol/Layer/Stack.hpp"

GraphicClientProtocol::Layer::StackElement::StackElement(void)
{
    assignLayer();
}

GraphicClientProtocol::Layer::StackElement::StackElement(GraphicClientProtocol::Layer::Color layer)
{
    assignLayer(layer);
}

void GraphicClientProtocol::Layer::StackElement::assignLayer(void)
{
    value.unknown = 0;
    type = GraphicClientProtocol::Layer::LayerType::UNKNOWN;
}

void GraphicClientProtocol::Layer::StackElement::assignLayer(GraphicClientProtocol::Layer::Color layer)
{
    value.color = layer;
    type = GraphicClientProtocol::Layer::LayerType::COLOR;
}
