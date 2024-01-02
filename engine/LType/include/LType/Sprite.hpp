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
    std::string filepath;
};

}
