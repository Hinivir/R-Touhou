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
    {sf::Keyboard::Left,    LType::InputList::LEFT},
    {sf::Keyboard::Right,   LType::InputList::RIGHT},
    {sf::Keyboard::Up,      LType::InputList::UP},
    {sf::Keyboard::Down,    LType::InputList::DOWN},
};
static const std::size_t KEYBOARD_TO_INPUT_LIST_LENGTH = sizeof(KEYBOARD_TO_INPUT_LIST) / sizeof(LibrarySFML::KeyboardToInputList);

}
