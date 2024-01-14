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

        namespace Serialization {
        template <typename T>
        std::vector<char> serialize(const T& data) {
            const char* rawData = reinterpret_cast<const char*>(&data);
            return std::vector<char>(rawData, rawData + sizeof(T));
        }

        template <typename T>
        T deserialize(const std::vector<char>& data) {
                if (data.size() != sizeof(T))
                    throw std::runtime_error("Deserialize error: Data size mismatch");
                T result;
                std::memcpy(&result, data.data(), sizeof(T));
                return result;
            }
    };

    struct player_t {
        std::size_t player_number;
        std::size_t pos_x;
        std::size_t pos_y;
        bool isConnected = false;
    };

    template <typename Component>
    struct server_message_t {
        std::size_t component_number;
        Component* component;
    };

class Client
{
  private:
    asio::io_context &ioContext_;
    asio::ip::udp::socket socket_;
    asio::ip::udp::endpoint serverEndpoint_;
    asio::ip::udp::endpoint senderEndpoint_;
    std::array<char, 1024> receiveBuffer_;

        player_t player;
        std::vector <player_t> players = {};
        std::vector<GameEngine::Entity> enemies = {};
        bool hasPos = false;

    public:
        using KeyFunction = std::function<void(bool)>;
        std::vector<GameEngine::Position> allPos;
        bool inGame = false;
        bool hasEnemy = false;
        bool startInit = false;
        std::size_t posNb = 0;

    Client(asio::io_context &ioContext, const std::string &serverAddress, const std::string &serverPort);
    ~Client();
    void sendMessage(const std::string &message);
    void getNewMessage();
    void handleMessageInGame(const std::string &message);
    void parseMessage(const std::string message);
    void addUsersWhenConnected(const std::string &message);
    void addNewUser(const std::string &message);

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
