/*
** EPITECH PROJECT, 2023
** R-Touhou
** File description:
** server_init.cpp
*/

#include "Server.hpp"

bool handleError(const int argc, const char **argv)
{
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <ip> <port>" << std::endl;
        return (false);
    }
    return (true);
}

int main(const int argc, const char **argv)
{
    std::string ip;
    std::string port;

    handleError(argc, argv);
    ip = argv[1];
    port = argv[2];
    Server server(ip, port);
    server.manageServer();
}
