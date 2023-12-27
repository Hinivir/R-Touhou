/*
** EPITECH PROJECT, 2023
** engine/LType/include/IEntity.hpp
** File description:
** -
*/

/// @file
/// @brief Interfaces for LType entities

#pragma once
#include "LType/Sprite.hpp"

namespace LType {

class IEntity
{
public:
    virtual ~IEntity() = default;
public:
    // << BASE >>

    // Init

    /// @brief Initialization of the game
    virtual void init(void) = 0;

    // << ATTRIBUTES >>

    // Sprite

    /// @brief Sets the value of the contained LType::Sprite
    virtual void setSprite(LType::Sprite const &sprite) = 0;
    /// @brief Gets a const reference to the contained LType::Sprite
    virtual LType::Sprite const &getSprite(void) const = 0;
    /// @brief Gets a reference to the contained LType::Sprite
    virtual LType::Sprite &getSprite(void) = 0;
};

}
