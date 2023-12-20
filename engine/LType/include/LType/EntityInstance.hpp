/*
** EPITECH PROJECT, 2023
** engine/LType/include/EntityInstance.hpp
** File description:
** -
*/

/// @file
/// @brief Instance of IEntity

#pragma once
#include <memory>
#include "LType/IEntity.hpp"

namespace LType {

using EntityInstance = std::shared_ptr<LType::IEntity>;
using EntityInstancePtr = std::weak_ptr<LType::IEntity>;

template <typename T>
static LType::EntityInstance createEntityInstance(void)
{
    return std::make_unique<T>();
}

}
