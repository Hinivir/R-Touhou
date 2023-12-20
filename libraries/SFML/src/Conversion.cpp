/*
** EPITECH PROJECT, 2023
** libraries/SFML/src/Conversion.cpp
** File description:
** -
*/

#include <LibrarySFML/Conversion.hpp>

sf::Color LibrarySFML::colorConversion(GraphicClientProtocol::Color const color)
{
    return sf::Color(
        static_cast<sf::Uint8>(color.r * 0x0FF),
        static_cast<sf::Uint8>(color.g * 0x0FF),
        static_cast<sf::Uint8>(color.b * 0x0FF),
        static_cast<sf::Uint8>(color.a * 0x0FF)
    );
}
