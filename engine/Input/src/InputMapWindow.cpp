/*
** EPITECH PROJECT, 2023
** engine/Input/src/InputMapWindow.cpp
** File description:
** -
*/

#include "Input/InputMapWindow.hpp"

Input::InputMapWindow::InputMapWindow(void)
{
    clearEvent();
}

// EVENTS

void Input::InputMapWindow::clearEvent(void)
{
    for (std::size_t i = 0; i < eventSize; i++)
        event[i] = false;
}

void Input::InputMapWindow::setEvent(Input::InputMapEvent const eventType, bool const value)
{
    if (eventType == Input::InputMapEvent::TOTAL)
        return;
    event[INPUT_INPUT_MAP_EVENT_TO_SIZE_T(eventType)] = value;
}

bool Input::InputMapWindow::getEvent(Input::InputMapEvent const eventType) const
{
    if (eventType == Input::InputMapEvent::TOTAL)
        return false;
    return event[INPUT_INPUT_MAP_EVENT_TO_SIZE_T(eventType)];
}

// INPUTS

void Input::InputMapWindow::setInput(Input::InputMapInput const inputId, Input::InputMapInputValue const value)
{
    if (inputId == Input::InputMapInput::TOTAL)
        return;
    input[INPUT_INPUT_MAP_INPUT_TO_SIZE_T(inputId)] = value;
}

Input::InputMapInputValue Input::InputMapWindow::getInput(Input::InputMapInput const inputId) const
{
    if (inputId == Input::InputMapInput::TOTAL)
        return Input::InputMapInputValue::NONE;
    return input[INPUT_INPUT_MAP_INPUT_TO_SIZE_T(inputId)];
}

void Input::InputMapWindow::clearInputs(void)
{
    for (std::size_t i = 0; i < inputSize; i++)
        input[i] = Input::InputMapInputValue::NONE;
}

void Input::InputMapWindow::prepareInputs(void)
{
    for (std::size_t i = 0; i < inputSize; i++)
        _inputUpdate[i] = false;
}

void Input::InputMapWindow::operator<<(Input::InputMapInput const inputId)
{
    if (inputId != Input::InputMapInput::TOTAL)
        _inputUpdate[INPUT_INPUT_MAP_INPUT_TO_SIZE_T(inputId)] = true;
}

void Input::InputMapWindow::confirmInputs(void)
{
    for (std::size_t i = 0; i < inputSize; i++) {
        if (_inputUpdate[i]) {
            input[i] = (input[i] == Input::InputMapInputValue::NONE) ? Input::InputMapInputValue::PRESSED : Input::InputMapInputValue::HELD;
        } else {
            input[i] = Input::InputMapInputValue::NONE;
        }
    }
}
