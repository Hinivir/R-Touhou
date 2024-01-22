/*
** EPITECH PROJECT, 2023
** R-Touhou
** File description:
** Server.hpp
*/

#ifndef R_TYPE_SERVER_HPP
#define R_TYPE_SERVER_HPP

#include <iostream>
#include <asio.hpp>
#include "../../Abstract/ANetwork.hpp"

class Server: protected ANetwork
{
    private:
        std::size_t _port;
        asio::ip::udp::socket socket;

    public:
        Server(const std::string &ip, const std::string &port);
        ~Server();
};

#endif //R_TYPE_SERVER_HPP
