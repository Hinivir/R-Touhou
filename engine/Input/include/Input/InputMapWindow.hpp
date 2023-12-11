/*
** EPITECH PROJECT, 2023
** engine/Input/include/InputMapWindow.hpp
** File description:
** -
*/

/// @file
/// @brief Class managing the inputs at the scale of a window

#pragma once
#include <vector>

#define INPUT_INPUT_MAP_EVENT_TO_SIZE_T(EVENT) static_cast<std::size_t>(EVENT)
#define INPUT_INPUT_MAP_EVENT_SIZE static_cast<std::size_t>(Input::InputMapEvent::TOTAL)

namespace Input {

enum class InputMapEvent {
    CLOSE,
    TOTAL,
};

class InputMapWindow {

public:
    InputMapWindow(void);
public:
    bool event[INPUT_INPUT_MAP_EVENT_SIZE];
    std::size_t eventSize = INPUT_INPUT_MAP_EVENT_SIZE;
public:
    /// @brief Sets the value of all events to `false`
    void clearEvent(void);
    /// @brief Sets the value of an event to `value`
    /// @param eventType (Input::InputMapEvent) Type of the event
    /// @param value (bool) New value of the event
    void setEvent(Input::InputMapEvent const eventType, bool const value);
    /// @brief Gets the value of an event
    /// @param eventType (Input::InputMapEvent) Type of the event
    bool getEvent(Input::InputMapEvent const eventType) const;

};

}
