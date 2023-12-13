/*
** EPITECH PROJECT, 2023
** engine/GraphicClientProtocol/src/Layer/StackMap.cpp
** File description:
** -
*/

#include "GraphicClientProtocol/Layer/StackMap.hpp"

GraphicClientProtocol::Layer::StackMapRef GraphicClientProtocol::Layer::createStackMapRef(void)
{
    return std::make_shared<GraphicClientProtocol::Layer::StackMap>();
}
