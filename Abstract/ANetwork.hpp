/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** ANetwork.hpp
*/

#ifndef ANETWORK_HPP
    #define ANETWORK_HPP

#include <iostream>
#include <array>

#include <asio.hpp>

template <typename senderMessage>
struct inGame_message {
    std::size_t index;
    senderMessage &message;
};

class ANetwork {
    protected:
        std::array<char, 2048> buffer;
        std::string ip;
        std::string port;
        asio::io_context ioContext;
        asio::ip::udp::socket socket;

    public:
        ANetwork(const std::string ip, const std::string port): ioContext(), socket(ioContext) {
            this->ip = ip;
            this->port = port;
        }
};
#endif
