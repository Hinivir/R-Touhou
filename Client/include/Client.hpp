/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Client.hpp
*/

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <cstdlib>
#include <array>

    #include <asio.hpp>
    #include <SFML/Window/Keyboard.hpp>
    #include "SparseArray.hpp"

    #include "Components/Components.hpp"
    #include "Entity.hpp"
    #include "ANetwork.hpp"

class Client: protected ANetwork
{
    private:
        asio::io_context ioContext;
        asio::ip::udp::socket socket;
        asio::ip::udp::endpoint senderEndpoint;
        asio::ip::udp::endpoint serverEndpoint;

    public:
        Client(const std::string ip, const std::string port);
        ~Client();
};
#endif
