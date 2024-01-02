/*
** EPITECH PROJECT, 2023
** engine/GraphicClientProtocol/src/Layer/Stack.cpp
** File description:
** -
*/

#include "GraphicClientProtocol/Layer/Stack.hpp"

#define NEW_GENERAL_ELEMENT(TYPE, NAME, UNION_NAME, ENUM_NAME) \
    GraphicClientProtocol::Layer::StackElement::StackElement(TYPE NAME) { assignLayer(NAME); } \
    void GraphicClientProtocol::Layer::StackElement::assignLayer(TYPE NAME) { value.UNION_NAME = NAME; type = ENUM_NAME; }

GraphicClientProtocol::Layer::StackElement::StackElement(void)
{
    assignLayer();
}

void GraphicClientProtocol::Layer::StackElement::assignLayer(void)
{
    value.unknown = 0;
    type = GraphicClientProtocol::Layer::LayerType::UNKNOWN;
}

NEW_GENERAL_ELEMENT(GraphicClientProtocol::Layer::Color, color, color, GraphicClientProtocol::Layer::LayerType::COLOR)

NEW_GENERAL_ELEMENT(GraphicClientProtocol::Layer::Sprites, sprites, sprites, GraphicClientProtocol::Layer::LayerType::SPRITES)
