/*
** EPITECH PROJECT, 2023
** engine/Input/include/InputMapRef.hpp
** File description:
** -
*/

/// @file
/// @brief Shared reference to an InputMap

#pragma once
#include <memory>
#include "Input/InputMap.hpp"

namespace Input {

    using InputMapRef = std::shared_ptr<Input::InputMap>;

    using InputMapWeakRef = std::weak_ptr<Input::InputMap>;

    /// @brief Create a new Input::InputMapRef
    /// @return Newly created reference
    Input::InputMapRef createInputMapRef(void);

}
