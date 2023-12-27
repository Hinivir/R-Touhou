/*
** EPITECH PROJECT, 2023
** engine/GraphicClientProtocol/src/Sprite.cpp
** File description:
** -
*/

#include "GraphicClientProtocol/Sprite.hpp"

GraphicClientProtocol::Sprite::Sprite(void)
{ }

GraphicClientProtocol::Sprite::Sprite(std::string const &filepath) : filepath(filepath)
{ }

void GraphicClientProtocol::Sprite::operator=(GraphicClientProtocol::Sprite const &other)
{
    filepath = other.filepath;
}

bool GraphicClientProtocol::Sprite::operator==(GraphicClientProtocol::Sprite const &other) const
{
    return filepath == other.filepath;
}

bool GraphicClientProtocol::Sprite::operator!=(GraphicClientProtocol::Sprite const &other) const
{
    return filepath != other.filepath;
}
