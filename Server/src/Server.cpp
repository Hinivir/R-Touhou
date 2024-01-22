/*
** EPITECH PROJECT, 2023
** R-Touhou
** File description:
** Server.cpp
*/

#include "../include/Server.hpp"

Server::Server(const std::string &ip, const std::string &port) :
    ANetwork::ANetwork(ip, port) ,socket(ioContext, asio::ip::udp::endpoint(asio::ip::udp::v4(), std::stoi(port)))
{
    _port = std::stoi(port);

    try {
        socket.close();
        socket.open(asio::ip::udp::v4());
        socket.bind(asio::ip::udp::endpoint(asio::ip::udp::v4(), _port));
    } catch (std::exception const &e) {
        std::cerr << "ERROR" << e.what() << std::endl;
        throw;
    }
}

Server::~Server(void)
{
    socket.close();
}
