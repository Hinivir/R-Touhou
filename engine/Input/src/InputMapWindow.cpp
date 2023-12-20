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
