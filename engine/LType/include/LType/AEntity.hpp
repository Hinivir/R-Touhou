/*
** EPITECH PROJECT, 2023
** engine/LType/include/AEntity.hpp
** File description:
** -
*/

/// @file
/// @brief Default implemenation of IEntity

#pragma once
#include "LType/IEntity.hpp"

namespace LType {

/// @brief Default implemenation of IEntity
class AEntity : public LType::IEntity
{
public:
    // << BASE >>

    // Init

    void init(void) override;

    // << ATTRIBUTES >>

    // Sprite

    void setSprite(LType::Sprite const &sprite) override;
    LType::Sprite const &getSprite(void) const override;
    LType::Sprite &getSprite(void) override;
protected:
    // Sprite
    LType::Sprite _sprite;
};

}
