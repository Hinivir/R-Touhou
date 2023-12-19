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
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <ip> <port>" << std::endl;
        return 1;
    }
    std::string const ip = argv[1];
    std::size_t const port = std::stoi(argv[2]);
    try {
        asio::io_context io_context;
        Client Client(io_context, ip, port);
        const std::string message = "Hello, server!";
        Client.sendMessage(message);
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
