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

    #include <asio.hpp>

    class Client {
    private:
        asio::io_context& ioContext_;
        asio::ip::udp::socket socket_;
        asio::ip::udp::endpoint serverEndpoint_;
        asio::ip::udp::endpoint senderEndpoint_;
        std::array<char, 1024> receiveBuffer_;


    public:
        Client(
            asio::io_context& ioContext,
            const std::string& serverAddress,
            const std::string& serverPort
        );
        ~Client();
        void sendMessage(const std::string& message);
        void getNewMessage();
};

#endif
