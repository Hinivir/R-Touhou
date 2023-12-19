/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Server.hpp
*/

#ifndef SERVER_HPP
    #define SERVER_HPP

    #include <iostream>
    #include <vector>
    #include <cstdlib>
    #include <cstring>

    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>

class Server
{
    private:
        std::string ip;
        std::size_t port;
        std::vector<std::size_t> clients;
        std::size_t axio;//tmp
        int serverSocket = 0;
        int clientSocket = 0;
        sockaddr_in serverAddress;

    public:
        Server(std::string const ip, std::size_t const port);
        ~Server(void);
        void setServer(void);
        void connectUser(void);
        void closeServer(void);
        void handleClient(int const clientSocket);
};
#endif
