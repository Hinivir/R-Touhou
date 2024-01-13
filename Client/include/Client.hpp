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

    #include "Components/Components.hpp"
    #include "Entity.hpp"

    struct player_t {
        std::size_t player_number;
        std::size_t pos_x;
        std::size_t pos_y;
        bool isConnected = false;
    };

    struct client_message_t {
        std::size_t player_number;
        sf::Keyboard key;
    };

    template <typename Component>
    struct server_message_t {
        std::size_t component_number;
        Component* component;
    };

class Client {
    private:
        asio::io_context& ioContext_;
        asio::ip::udp::socket socket_;
        asio::ip::udp::endpoint serverEndpoint_;
        asio::ip::udp::endpoint senderEndpoint_;
        std::array<char, 1024> receiveBuffer_;

        player_t player;
        std::vector <player_t> players = {};

    public:
        using KeyFunction = std::function<void(bool)>;
        bool inGame = false;

        Client(
            asio::io_context& ioContext,
            const std::string& serverAddress,
            const std::string& serverPort
        );
        ~Client();
        void sendMessage(const std::string& message);
        void sendMessage(const client_message_t& message);
        void getNewMessage();
        void handleMessageInGame(const std::string& message);
        void parseMessage(const std::string message);
        void addUsersWhenConnected(const std::string& message);
        void addNewUser(const std::string& message);
        std::vector<GameEngine::Entity> receiveEnemies();

        void runGameTmp();

        void upFunction(std::size_t player_number);
        void downFunction(std::size_t player_number);
        void leftFunction(std::size_t player_number);
        void rightFunction(std::size_t player_number);
        void actionFunction(std::size_t player_number);
        void quitFunction(std::size_t player_number);

        void initGame(std::string const gamename);
        void runGame(std::string const gamename);
};
#endif
