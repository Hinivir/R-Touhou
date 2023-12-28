/*
** EPITECH PROJECT, 2023
** engine/LType/src/Sprite.cpp
** File description:
** -
*/

#include "LType/Sprite.hpp"

LType::Sprite::Sprite(void)
{ }

LType::Sprite::Sprite(std::string const &filepath) : filepath(filepath)
{ }

void LType::Sprite::operator=(LType::Sprite const &other)
{
    filepath = other.filepath;
}

bool LType::Sprite::operator==(LType::Sprite const &other) const
{
    return filepath == other.filepath;
}

bool LType::Sprite::operator!=(LType::Sprite const &other) const
{
    return filepath != other.filepath;
}
