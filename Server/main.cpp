/*
** EPITECH PROJECT, 2023
** R-Touhou
** File description:
** server_init.cpp
*/

#include "Server.hpp"
#include "ANetwork.hpp"
#include <sstream>

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
    if (!handleError(argc, argv))
        return 84;
    Server server(argv[1], argv[2]);
    server.receiveMessage(true);
    asio::io_context &io_context(server.getIoContext());
    std::thread t([&io_context]() { io_context.run(); });
    while (server.isConnected()) {
        std::string message;
        std::getline(std::cin, message);
        message += "\n";
        std::cout << "you wrote: " << message << std::endl;
//        server.sendMessage<std::string>(message, server.serverEndpoint, true);
    }
    io_context.stop();
    t.join();
    return 0;
}
