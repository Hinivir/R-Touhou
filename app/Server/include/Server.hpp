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

    #define CONNECTED "101: You are connected!\n"
    #define DISCONNECTED "103: You are disconnected!\n"
    #define ERROR "102: Error sending confirmation message to client!\n"
    #define READY "104: You are ready!\n"
    #define SERVER_FULL "105: Server is full!\n"
    using asio::ip::udp;

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
            bool inGame = false;

        public:
            Server(const std::string& ip, int const port);
            ~Server(void);
            static const std::map<std::string, std::function<void(Server &, const udp::endpoint&, const std::array<char, 2048>&, size_t)>> serverCommandHandler;
            void handleConnect(const udp::endpoint& client_endpoint, const std::array<char, 2048>& buffer, size_t bytes_received);
            void handleDisconnect(const udp::endpoint& client_endpoint, const std::array<char, 2048>& buffer, size_t bytes_received);
            void handleReady(const udp::endpoint& client_endpoint, const std::array<char, 2048>& buffer, size_t bytes_received);
            void closeServer(void);
            void startServer(void);
            void connectClient(const udp::endpoint& client_endpoint, const std::array<char, 2048>& buffer, size_t bytes_received);
            void acceptClients(void);
            void broadcastMessage(const std::string& message, size_t messageSize, const udp::endpoint& sender);
            void notifyGameReady(void);

            void runGame(std::string const gamename);
    };
#endif

