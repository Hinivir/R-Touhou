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
    asio::io_context ioContext;
    Client new_client(argv[1], argv[2]);
    new_client.receiveMessage(true);

    /*
    new_client.getNewMessage();
    std::thread ioThread([&ioContext]() { ioContext.run(); });
    for (;;) {
        if (!new_client.inGame) {
            std::string newMessage = {0};
            std::getline(std::cin, newMessage);
            newMessage += "\n";
            new_client.sendMessage(newMessage);
        }
    }
    ioContext.stop();
    ioThread.join();
    */
    return 0;
}
