/*
** EPITECH PROJECT, 2023
** libraries/SFML/src/Instance.cpp
** File description:
** -
*/

#include <iostream>
#include "LibrarySFML/Instance.hpp"

LibrarySFML::Instance::Instance(void)
{
    std::cout << "SFML: open" << std::endl;
}

LibrarySFML::Instance::~Instance()
{
    std::cout << "SFML: close" << std::endl;
}
