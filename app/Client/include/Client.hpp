/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Client.hpp
*/

#ifndef CLIENT_HPP
    #define CLIENT_HPP

    #include <iostream>
    #include <vector>
    #include <cstdlib>
    #include <cstring>
    #include <queue>

    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>

class Client
{
    private:
        std::string ip;
        std::size_t port;
        sockaddr_in serverAddress;
        int userSocket = 0;
        std::queue<std::string> messageQueue;

    public:
        Client(std::string const ip, std::size_t const port);
        ~Client(void);
        void connectClient(void);
        void closeClient(void);
        void sendMessage(std::string const message);
        void getMessage(void);
        void runClient(void);
};
#endif
