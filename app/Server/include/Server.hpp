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
    #include <asio.hpp>

using asio::ip::udp;

class Server
{
    private:
        asio::io_service io_service;
        udp::socket server_socket;
        std::vector<udp::endpoint> connectedClients;

    public:
        Server(const std::string& ip, int const port);
        ~Server(void);
        void closeServer(void);
        void startServer(void);
        void connectClient(const udp::endpoint& client_endpoint, const std::array<char, 2048>& buffer, size_t bytes_received);
        void acceptClients(void);
        void broadcastMessage(const std::array<char, 2048>& buffer, size_t bytes_received, const udp::endpoint& sender);
};
#endif
