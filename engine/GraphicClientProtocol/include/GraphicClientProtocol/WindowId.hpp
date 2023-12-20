/*
** EPITECH PROJECT, 2023
** engine/GraphicClientProtocol/include/WindowId.hpp
** File description:
** -
*/

/// @file
/// @brief Id of a window

#pragma once
#include <cstddef>

#define GRAPHIC_WINDOWID_DEFAULT 0
#define GRAPHIC_WINDOWID_MAX 8

namespace GraphicClientProtocol {

using WindowId = std::size_t;

}
