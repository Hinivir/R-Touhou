/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** main.cpp
*/

#include "include/Client.hpp"
#include <iostream>

static bool handle_error(int const argc, char const *const *const argv)
{
    if (argc != 3) {
        std::cerr << "ERROR: invalid number of arguments" << std::endl;
        return false;
    }
    return true;
}

int main(int const argc, char const *const *const argv)
{
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <ip> <port>" << std::endl;
        return 1;
    }
    Client new_client(argv[1], argv[2]);
    new_client.receiveMessage<std::string>(true);
    std::cout << new_client.getBuffer().begin() << std::endl;
    asio::io_context &io_context(new_client.getIoContext());
    std::thread t([&io_context]() { io_context.run(); });
    for (;;) {
        std::string message;
        std::getline(std::cin, message);
        message += "\n";
        new_client.sendMessage<std::string>(message, new_client.serverEndpoint, true);
    }
    io_context.stop();
    t.join();
    return 0;
}
