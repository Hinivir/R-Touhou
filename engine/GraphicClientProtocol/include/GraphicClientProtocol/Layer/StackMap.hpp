/*
** EPITECH PROJECT, 2023
** engine/GraphicClientProtocol/include/GraphicClientProtocol/Layer/StackMap.hpp
** File description:
** -
*/

/// @file
/// @brief List of multiple stacks of multiple Layers. It does not inherit from Layer

#pragma once
#include <map>
#include <memory>
#include <vector>
#include "GraphicClientProtocol/Layer/Stack.hpp"
#include "GraphicClientProtocol/WindowId.hpp"

namespace GraphicClientProtocol { namespace Layer {

using StackMap = std::map<GraphicClientProtocol::WindowId, GraphicClientProtocol::Layer::Stack>;

using StackMapRef = std::shared_ptr<GraphicClientProtocol::Layer::StackMap>;

using StackMapWeakRef = std::weak_ptr<GraphicClientProtocol::Layer::StackMap>;

/// @brief Create a new GraphicClientProtocol::Layer::StackMapRef
/// @return Newly created reference
GraphicClientProtocol::Layer::StackMapRef createStackMapRef(void);

}}
