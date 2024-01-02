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

    // Area

    void setArea(LType::Attribute::Size const &area) override;
    LType::Attribute::Size const &getArea(void) const override;
    LType::Attribute::Size &getArea(void) override;

    void setAreaSetToTexture(bool const areaSetToTexture) override;
    bool const getAreaSetToTexture(void) const override;
    bool &getAreaSetToTexture(void) override;

    // Position

    void setPosition(LType::Attribute::Position const &position) override;
    LType::Attribute::Position const &getPosition(void) const override;
    LType::Attribute::Position &getPosition(void) override;

    // Sprite

    void setSprite(LType::Sprite const &sprite) override;
    LType::Sprite const &getSprite(void) const override;
    LType::Sprite &getSprite(void) override;

protected:
    /// @brief Size of the area, for collisions
    LType::Attribute::Position _area = LType::Attribute::Position(0.0, 0.0, 0.0);
    /// @brief If the graphic library needs to set the area size to the texture size
    bool _areaSetToTexture = false;
    /// @brief Position of the entity
    LType::Attribute::Position _position = LType::Attribute::Position(0.0, 0.0, 0.0);
    /// @brief Sprite used
    LType::Sprite _sprite;
};

}
