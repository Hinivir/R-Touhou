/*
** EPITECH PROJECT, 2023
** engine/LType/include/Sprite.hpp
** File description:
** -
*/

/// @file
/// @brief Class containing display information for entity's sprites

#pragma once
#include <iostream>
#include "LType/Color.hpp"

namespace LType {

class Sprite
{
public:
    // << CONSTRUCTORS >>

    Sprite(void);
    /// @param filepath Filepath of the ressource used to display
    Sprite(std::string const &filepath);

    // << OPERATORS >>

    /// @brief Equal operator overwrite, setting the attributes of this sprite to another's
    void operator=(LType::Sprite const &other);

    // Comparing

    /// @brief Equality operator overwrite
    /// @return True if all the attributes are the same. Otherwise, False
    bool operator==(LType::Sprite const &other) const;
    /// @brief Inequality operator overwrite
    /// @return False if all the attributes are the same. Otherwise, True
    bool operator!=(LType::Sprite const &other) const;
public:
    /// @brief If the sprite has to be centered, relative to its size
    bool center = true;
    /// @brief If the sprite has to be flipped horizontaly
    bool flipH = false;
    /// @brief If the sprite has to be flipped vertically
    bool flipV = false;
    /// @brief Filepath of the sprite
    std::string filepath;
    /// @brief If the sprite has to be hidden
    bool hidden = false;
    /// @brief Color to apply on the sprite, including the alpha channel
    LType::Color modulate;
};

}
