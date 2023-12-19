/*
** EPITECH PROJECT, 2023
** R-Touhou
** File description:
** server_init.cpp
*/

#include "include/Server.hpp"
#include <sstream>

static bool handle_error(int const argc, char const * const * const argv) {
    if (argc != 3) {
        std::cerr << "ERROR: invalid number of arguments" << std::endl;
        return true;
    }
    std::stringstream ss(argv[2]);
    std::size_t port;
    ss >> port;
    if (ss.fail()) {
        std::cerr << "ERROR: invalid port \"" << argv[2] << "\"" << std::endl;
        return true;
    }
    return false;
}

static std::size_t get_port(char const * const portString) {
    std::stringstream ss(portString);
    std::size_t port;
    ss >> port;
    return port;
}

int main(int const argc, char const * const * const argv) {
    if (handle_error(argc, argv))
        return 84;
    std::size_t const port = get_port(argv[2]);
    Server server(argv[1], port);
    server.setServer();
    server.connectUser();
    return 0;
}
