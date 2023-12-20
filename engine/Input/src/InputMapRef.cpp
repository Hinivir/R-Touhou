/*
** EPITECH PROJECT, 2023
** engine/Input/src/InputMapRef.cpp
** File description:
** -
*/

#include "Input/InputMapRef.hpp"

Input::InputMapRef Input::createInputMapRef(void)
{
    return std::make_shared<Input::InputMap>();
}
