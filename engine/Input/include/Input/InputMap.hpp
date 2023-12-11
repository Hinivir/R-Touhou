/*
** EPITECH PROJECT, 2023
** engine/Input/include/InputMap.hpp
** File description:
** -
*/

/// @file
/// @brief Class managing inputs and events from the graphic manager

#pragma once
#include <map>
#include "Graphic/WindowId.hpp"
#include "Input/InputMapWindow.hpp"

namespace Input {

class InputMap {

public:
    std::map<Graphic::WindowId, Input::InputMapWindow> window;
public:
    Input::InputMapWindow mergeWindows(void) const;

};

}
