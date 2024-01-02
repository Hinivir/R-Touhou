/*
** EPITECH PROJECT, 2023
** libraries/LType/include/LType/InputList.hpp
** File description:
** -
*/

/// @file
/// @brief Every input that can be used by games

#pragma once

namespace LType {

/// @brief List of all inputs supported by LType
enum class InputList {
    // Text

    /// @brief Colon key (:)
    KEY_COLON,
    /// @brief Comma key (,)
    KEY_COMMA,
    /// @brief Period key (.)
    KEY_PERIOD,
    /// @brief Semicolon key (;)
    KEY_SEMICOLON,
    /// @brief Spacebar
    KEY_SPACE,

    // Numbers

    /// @brief 0 keys (Num and Numpad)
    KEY_0,
    /// @brief 1 keys (Num and Numpad)
    KEY_1,
    /// @brief 2 keys (Num and Numpad)
    KEY_2,
    /// @brief 3 keys (Num and Numpad)
    KEY_3,
    /// @brief 4 keys (Num and Numpad)
    KEY_4,
    /// @brief 5 keys (Num and Numpad)
    KEY_5,
    /// @brief 6 keys (Num and Numpad)
    KEY_6,
    /// @brief 7 keys (Num and Numpad)
    KEY_7,
    /// @brief 8 keys (Num and Numpad)
    KEY_8,
    /// @brief 9 keys (Num and Numpad)
    KEY_9,

    // Specials

    /// @brief Escape key
    KEY_ESC,
    /// @brief Return key
    KEY_RETURN,

    // Actions

    /// @brief Down arrow
    DOWN,
    /// @brief Left arrow
    LEFT,
    /// @brief Right arrow
    RIGHT,
    /// @brief Up arrow
    UP,

    // Other

    /// @brief Total amount of supported keys
    TOTAL,
};

}
