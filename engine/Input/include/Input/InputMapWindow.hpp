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
#include "LType/InputList.hpp"

#define INPUT_INPUT_MAP_EVENT_TO_SIZE_T(EVENT) static_cast<std::size_t>(EVENT)
#define INPUT_INPUT_MAP_EVENT_SIZE static_cast<std::size_t>(Input::InputMapEvent::TOTAL)

#define INPUT_INPUT_MAP_INPUT_TO_SIZE_T(INPUT) static_cast<std::size_t>(INPUT)
#define INPUT_INPUT_MAP_INPUT_SIZE static_cast<std::size_t>(LType::InputList::TOTAL)

namespace Input {

enum class InputMapEvent {
    CLOSE,
    TOTAL,
};

using InputMapInput = LType::InputList;
enum class InputMapInputValue {
    NONE,
    PRESSED,
    HELD,
};

class InputMapWindow {

public:
    InputMapWindow(void);
public:
    bool event[INPUT_INPUT_MAP_EVENT_SIZE];
    std::size_t eventSize = INPUT_INPUT_MAP_EVENT_SIZE;
    Input::InputMapInputValue input[INPUT_INPUT_MAP_INPUT_SIZE];
    std::size_t inputSize = INPUT_INPUT_MAP_EVENT_SIZE;
private:
    /// @brief List of inputs that have been updated this frame
    bool _inputUpdate[INPUT_INPUT_MAP_INPUT_SIZE];
public:
    // EVENTS

    /// @brief Sets the value of all events to `false`
    void clearEvent(void);
    /// @brief Sets the value of an event to `value`
    /// @param eventType (Input::InputMapEvent) Type of the event
    /// @param value (bool) New value of the event
    void setEvent(Input::InputMapEvent const eventType, bool const value);
    /// @brief Gets the value of an event
    /// @param eventType (Input::InputMapEvent) Type of the event
    bool getEvent(Input::InputMapEvent const eventType) const;

    // INPUTS

    /// @brief Needs to be used BEFORE calling `operator<<` and `confirmInputs`
    void prepareInputs(void);
    /// @brief Adds a value to `_inputUpdate`
    /// @param inputId (Input::InputMapInput) Type of the input
    void operator<<(Input::InputMapInput const inputId);
    /// @brief Needs to be used AFTER calling `prepareInputs` and `operator<<`
    void confirmInputs(void);

    /// @brief Sets the value of all inputs to `NONE`
    void clearInputs(void);

    /// @brief Sets the value of an input to `value`
    /// @param inputId (Input::InputMapInput) Type of the input
    /// @param value (Input::InputMapInputValue) New value of the input
    void setInput(Input::InputMapInput const inputId, Input::InputMapInputValue const value);
    /// @brief Gets the value of an input
    /// @param inputId (Input::InputMapInput) Type of the input
    Input::InputMapInputValue getInput(Input::InputMapInput const inputId) const;


};

}
