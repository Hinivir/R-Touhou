/*
** EPITECH PROJECT, 2023
** engine/LType/include/IEntity.hpp
** File description:
** -
*/

/// @file
/// @brief Interfaces for LType entities

#pragma once

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
};

}
