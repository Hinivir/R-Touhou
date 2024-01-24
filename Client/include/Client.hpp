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

class Client: public ANetwork
{
    private:
        asio::ip::udp::endpoint senderEndpoint;

    public:
        asio::ip::udp::endpoint serverEndpoint;
        Client(const std::string ip, const std::string port);
        ~Client();
        void handleMessage();
        void handleMessageClient(std::string &message) override;
        void commandConnect();
        void commandDisconnect();
        void commandError();
        void commandReady();
        void commandFull();
};
#endif
