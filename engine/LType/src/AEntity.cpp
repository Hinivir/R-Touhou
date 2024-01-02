/*
** EPITECH PROJECT, 2023
** engine/LType/src/AEntity.cpp
** File description:
** -
*/

#include "LType/AEntity.hpp"

void LType::AEntity::init(void)
{ }

// Sprite

void LType::AEntity::setSprite(LType::Sprite const &sprite)
{
    _sprite = sprite;
}

LType::Sprite const &LType::AEntity::getSprite(void) const
{
    return _sprite;
}

LType::Sprite &LType::AEntity::getSprite(void)
{
    return _sprite;
}

// Position

void LType::AEntity::setPosition(LType::Attribute::Position const &position)
{
    _position = position;
}

LType::Attribute::Position const &LType::AEntity::getPosition(void) const
{
    return _position;
}

LType::Attribute::Position &LType::AEntity::getPosition(void)
{
    return _position;
}
