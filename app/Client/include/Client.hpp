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

typedef struct {
    std::size_t player_number;
    std::size_t pos_x;
    std::size_t pos_y;
    bool isConnected = false;
} player_t;

class Client {
    private:
        asio::io_context& ioContext_;
        asio::ip::udp::socket socket_;
        asio::ip::udp::endpoint serverEndpoint_;
        asio::ip::udp::endpoint senderEndpoint_;
        std::array<char, 1024> receiveBuffer_;

        player_t player;
        std::vector <player_t> players = {};
        bool inGame = false;

    public:
        using KeyFunction = std::function<void(bool)>;

        Client(asio::io_context& ioContext, const std::string& serverAddress, const std::string& serverPort);
        ~Client();
        void sendMessage(const std::string& message);
        void getNewMessage();
        void handleMessageInGame(const std::string& message);
        void parseMessage(const std::string message);
        void addUsersWhenConnected(const std::string& message);
        void addNewUser(const std::string& message);

        void runGame();

        void upFunction(std::size_t player_number);
        void downFunction(std::size_t player_number);
        void leftFunction(std::size_t player_number);
        void rightFunction(std::size_t player_number);
        void actionFunction(std::size_t player_number);
        void quitFunction(std::size_t player_number);
};
#endif
