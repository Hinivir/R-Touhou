/*
** EPITECH PROJECT, 2023
** engine/LType/src/AEntity.cpp
** File description:
** -
*/

#include "LType/AEntity.hpp"

void LType::AEntity::init(void)
{ }

// Area

void LType::AEntity::setArea(LType::Attribute::Size const &area)
{
    _area = area;
}

LType::Attribute::Size const &LType::AEntity::getArea(void) const
{
    return _area;
}

LType::Attribute::Size &LType::AEntity::getArea(void)
{
    return _area;
}

void LType::AEntity::setAreaSetToTexture(bool const areaSetToTexture)
{
    _areaSetToTexture = areaSetToTexture;
}

bool const LType::AEntity::getAreaSetToTexture(void) const
{
    return _areaSetToTexture;
}

bool &LType::AEntity::getAreaSetToTexture(void)
{
    return _areaSetToTexture;
}

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
