/*
** EPITECH PROJECT, 2023
** libraries/SFML/include/LibrarySFML/Conversion.hpp
** File description:
** -
*/

#pragma once
#include <SFML/Graphics/Color.hpp>
#include "GraphicClientProtocol/Color.hpp"

namespace LibrarySFML {

sf::Color colorConversion(GraphicClientProtocol::Color const color);

}
