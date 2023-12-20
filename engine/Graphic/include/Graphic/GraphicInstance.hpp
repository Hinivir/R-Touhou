/*
** EPITECH PROJECT, 2023
** engine/Graphic/include/GraphicInstance.hpp
** File description:
** -
*/

/// @file
/// @brief Instance of IGraphic

#pragma once
#include <Graphic/IGraphic.hpp>
#include <memory>

namespace Graphic {

using GraphicInstance = std::unique_ptr<Graphic::IGraphic>;

template <typename T>
static Graphic::GraphicInstance createGraphicInstance(void)
{
    return std::make_unique<T>();
}

}
