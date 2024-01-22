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
        //vector pour server
        //endpoint pour client

    public:
        ANetwork(const std::string ip, const std::string port);
        ~ANetwork();

        void sendMessageString(const std::string &message, asio::ip::udp::endpoint &endpoint);//override

        template<typename T>
        void sendMessageStruct(const T &message, asio::ip::udp::endpoint &endpoint);//override

        std::string receiveMessageString();//override

        template<typename Component>
        Component receiveMessageStruct();//override
};
#endif
