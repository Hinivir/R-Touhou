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
        std::vector<std::size_t> clients;//tmp
        std::size_t axio;//tmp
        std::size_t serverSocket = 0;
        std::size_t clientSocket = 0;
        sockaddr_in serverAddress;
    
    public:
        Server(std::string ip, std::size_t port);
        ~Server();
        void setServer();
        void connectUser();
        void closeServer();
};
#endif
