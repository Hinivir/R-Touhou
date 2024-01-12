/*
** EPITECH PROJECT, 2024
** R-Touhou_Bootstrap
** File description:
** Window
*/

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

namespace GameEngine
{
    struct Window
    {
        std::size_t width;
        std::size_t height;
        int resfresh_rate;
        std::string title;
        sf::RenderWindow window;
    };
} // namespace GameEngine

#endif /* !WINDOW_HPP_ */
