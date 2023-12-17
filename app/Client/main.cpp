/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** main.cpp
*/

#include "include/Client.hpp"
#include <iostream>

static bool handle_error(int const argc, char const * const * const argv)
{
    if (argc != 3) {
        std::cerr << "ERROR: invalid number of arguments" << std::endl;
        return false;
    }
    return true;
}

int main(int const argc, char const * const * const argv)
{
    if (!handle_error(argc, argv))
        return 84;
    std::string const ip = argv[1];
    std::size_t const port = std::stoi(argv[2]);
    Client client(ip, port);

    client.connectClient();
    client.runClient();
    return 0;
}
