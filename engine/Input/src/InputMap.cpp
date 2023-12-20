/*
** EPITECH PROJECT, 2023
** engine/Input/src/InputMap.cpp
** File description:
** -
*/

#include "Input/InputMap.hpp"

Input::InputMapWindow Input::InputMap::mergeWindows(void) const
{
    Input::InputMapWindow mergedWindow;

    for (auto const &[_, windowCurrent] : window) {
        for (std::size_t i = 0; i < windowCurrent.eventSize; i++) {
            if (windowCurrent.event[i])
                mergedWindow.event[i] = true;
        }
    }
    return mergedWindow;
}
