/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Client.hpp
*/

#ifndef CLIENT_HPP
#define CLIENT_HPP

    #include <iostream>
    #include <queue>
    #include <asio.hpp>

    class Client {
    private:
        asio::ip::udp::socket socket_;
        asio::ip::udp::endpoint server_endpoint_;

    public:
        Client(asio::io_context& io_context, const std::string& server_ip, std::size_t server_port);
        void sendMessage(const std::string& message);

};

#endif
