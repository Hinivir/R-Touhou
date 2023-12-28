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
        std::size_t x = 0;
        std::size_t y = 0;
        std::size_t other_player_x = 0;
        std::size_t other_player_y = 0;
        bool inGame = false;

    public:
        using KeyFunction = std::function<void(bool)>;

        Client(
            asio::io_context& ioContext,
            const std::string& serverAddress,
            const std::string& serverPort
        );
        ~Client();
        void handleMessageInGame(const std::string& message);
        void sendMessage(const std::string& message);
        void getNewMessage();
        void run_game();

        void upFunction(bool isReceived);
        void downFunction(bool isReceived);
        void leftFunction(bool isReceived);
        void rightFunction(bool isReceived);
        void actionFunction(bool isReceived);
        void quitFunction(bool isReceived);
};
#endif
