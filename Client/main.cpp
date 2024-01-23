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
    asio::io_context &io_context = new_client.getIoContext();
    new_client.receiveMessage(true);
    asio::thread t([&io_context]() { io_context.run(); std::cout << "thread" << std::endl;});
    for (;;) {
        std::string message;
        std::getline(std::cin, message);
        if (message == "quit")
            break;
        new_client.sendMessage(message, new_client.serverEndpoint, true);
        std::cout << "message sent" << std::endl;
    }

    io_context.stop();
    t.join();
    return 0;
}
