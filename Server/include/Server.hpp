/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Server.hpp
*/

#ifndef SERVER_HPP
    #define SERVER_HPP

    #include <iostream>
    #include <vector>
    #include <asio.hpp>
    #include <map>
    #include <SFML/Window/Keyboard.hpp>

    #include "Entity.hpp"

    #define CONNECTED "101: You are connected!\n"
    #define DISCONNECTED "103: You are disconnected!\n"
    #define ERROR "102: Error sending confirmation message to client!\n"
    #define READY "104: You are ready!\n"
    #define SERVER_FULL "105: Server is full!\n"
    using asio::ip::udp;


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
    }

    template <typename Component>
    struct server_message_t {
        std::size_t player_number;
        Component* component;
    };

    class Server
    {
        private:
            size_t playerCount = 0;
            size_t maxPlayers = 4;
            bool isChatLocked = false;
            asio::io_context io_service;
            udp::socket server_socket;
            size_t nextPlayerNumber = 1;
            std::map<udp::endpoint, int> playerNumberMap;
            std::vector<udp::endpoint> alreadyConnectedClients;
            std::vector<udp::endpoint> connectedClients;
            std::vector<udp::endpoint> readyClients;
            std::vector<udp::endpoint> initClients;
            bool inGame = false;

        public:
            Server(const std::string& ip, int const port);
            ~Server(void);
            static const std::map<std::string, std::function<void(Server &, const udp::endpoint&, const std::array<char, 2048>&, size_t)>> serverCommandHandler;
            void handleConnect(const udp::endpoint& client_endpoint, const std::array<char, 2048>& buffer, size_t bytes_received);
            void handleDisconnect(const udp::endpoint& client_endpoint, const std::array<char, 2048>& buffer, size_t bytes_received);
            void handleReady(const udp::endpoint& client_endpoint, const std::array<char, 2048>& buffer, size_t bytes_received);
            void handleGameInit(const udp::endpoint& client_endpoint, const std::array<char, 2048>& buffer, size_t bytes_received);
            void closeServer(void);
            void startServer(void);
            void connectClient(const udp::endpoint& client_endpoint, const std::array<char, 2048>& buffer, size_t bytes_received);
            void acceptClients(void);
            void broadcastMessage(const std::string& message, size_t messageSize, const udp::endpoint& sender);
            template <typename T>
            void broadcastStructure(server_message_t<T>& info, size_t size, const udp::endpoint& sender) {
                std::vector<char> serializedData = Serialization::serialize(info);

                for (const auto& client : connectedClients) {
                    if (client != sender) {
                        try {
                            server_socket.send_to(asio::buffer(serializedData), client);
                        } catch (const std::exception& e) {
                            std::cerr << "Error broadcasting structure to client: " << e.what() << std::endl;
                        }
                    }
                }
            }
            void notifyGameReady(void);
            void sendEnemies(std::vector<GameEngine::Entity> &enemies);

            void runGame(std::string const gamename);
            void initGame(std::string const gamename);
    };
#endif
