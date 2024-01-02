/*
** EPITECH PROJECT, 2023
** libraries/SFML/include/LibrarySFML/Inputs.hpp
** File description:
** -
*/

/// @file
/// @brief Data about converting keys into LType inputs

#pragma once
#include <cstddef>
#include <SFML/Window/Keyboard.hpp>
#include "LType/InputList.hpp"

namespace LibrarySFML {

using KeyboardToInputList = struct KeyboardToInputList_s {
    sf::Keyboard::Key keyboard;
    LType::InputList input;
};

static const LibrarySFML::KeyboardToInputList KEYBOARD_TO_INPUT_LIST[] = {
    // Numbers
    {sf::Keyboard::Num0,    LType::InputList::KEY_0},
    {sf::Keyboard::Num1,    LType::InputList::KEY_1},
    {sf::Keyboard::Num2,    LType::InputList::KEY_2},
    {sf::Keyboard::Num3,    LType::InputList::KEY_3},
    {sf::Keyboard::Num4,    LType::InputList::KEY_4},
    {sf::Keyboard::Num5,    LType::InputList::KEY_5},
    {sf::Keyboard::Num6,    LType::InputList::KEY_6},
    {sf::Keyboard::Num7,    LType::InputList::KEY_7},
    {sf::Keyboard::Num8,    LType::InputList::KEY_8},
    {sf::Keyboard::Num9,    LType::InputList::KEY_9},
    {sf::Keyboard::Numpad0, LType::InputList::KEY_0},
    {sf::Keyboard::Numpad1, LType::InputList::KEY_1},
    {sf::Keyboard::Numpad2, LType::InputList::KEY_2},
    {sf::Keyboard::Numpad3, LType::InputList::KEY_3},
    {sf::Keyboard::Numpad4, LType::InputList::KEY_4},
    {sf::Keyboard::Numpad5, LType::InputList::KEY_5},
    {sf::Keyboard::Numpad6, LType::InputList::KEY_6},
    {sf::Keyboard::Numpad7, LType::InputList::KEY_7},
    {sf::Keyboard::Numpad8, LType::InputList::KEY_8},
    {sf::Keyboard::Numpad9, LType::InputList::KEY_9},
    // Arrows
    {sf::Keyboard::Left,    LType::InputList::LEFT},
    {sf::Keyboard::Right,   LType::InputList::RIGHT},
    {sf::Keyboard::Up,      LType::InputList::UP},
    {sf::Keyboard::Down,    LType::InputList::DOWN},
};
static const std::size_t KEYBOARD_TO_INPUT_LIST_LENGTH = sizeof(KEYBOARD_TO_INPUT_LIST) / sizeof(LibrarySFML::KeyboardToInputList);

}
