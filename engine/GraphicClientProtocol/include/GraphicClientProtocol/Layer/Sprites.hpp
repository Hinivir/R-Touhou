/*
** EPITECH PROJECT, 2023
** engine/GraphicClientProtocol/include/GraphicClientProtocol/Layer/Sprites.hpp
** File description:
** -
*/

/// @file
/// @brief Layer of multiple entites, displaying their sprites on the same layer

#pragma once
#include <list>
#include "GraphicClientProtocol/Layer/Base.hpp"
#include "LType/EntityInstance.hpp"

namespace GraphicClientProtocol { namespace Layer {

/// @brief Layer of multiple entities, displaying their sprites on the same layer
class Sprites : public GraphicClientProtocol::Layer::Base {

public:
    /// @brief List containing every entity of the layer
    std::list<LType::EntityInstancePtr> content;

};

}}
