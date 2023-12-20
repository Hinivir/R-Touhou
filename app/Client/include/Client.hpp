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
    #include <vector>
    #include <cstdlib>

    #include <asio.hpp>
    #include <SFML/Graphics.hpp>

    class Client {
    private:
        bool disconnectFlag_ = false;
        asio::ip::udp::socket socket_;
        asio::ip::udp::endpoint server_endpoint_;
        std::array<char, 1024> recv_buf_;
        std::string input_buffer_;
        std::mutex input_mutex_;
        std::queue<std::string> history_received_messages;

    public:
        Client(asio::io_context& io_context, const std::string& server_ip, std::size_t server_port);
        ~Client();
        void sendMessage(const std::string& message);
        void getNewMessage();
        void runClient();

        void start_game();
};

#endif
