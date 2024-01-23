/*
** EPITECH PROJECT, 2023
** R-Touhou
** File description:
** Server.hpp
*/

#ifndef R_TYPE_SERVER_HPP
#define R_TYPE_SERVER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <asio.hpp>
#include "../../Abstract/ANetwork.hpp"

#define CONNECTED "101: You are connected!\n"
#define DISCONNECTED "103: You are disconnected!\n"
#define ERROR_MSG "102: Error sending confirmation message to client!\n"
#define READY "104: You are ready!\n"
#define SERVER_FULL "105: Server is full!\n"

class Server: protected ANetwork
{
    private:
        std::size_t _port;
        std::size_t maxPlayers = 4;
        std::size_t  playerNumber = 0;
        std::vector<asio::ip::udp::endpoint> clients;
        std::map<asio::ip::udp::endpoint, int> playerNumberMap;

    public:
        static const std::map<std::string, std::function<void(Server&, const asio::ip::udp::endpoint&, const std::array<char, 2048>&, size_t)>> commandHandler;
        Server(const std::string &ip, const std::string &port);
        ~Server();
        void manageServer();
        void verifConnected();
        void manageMessage();
        void handleReady(const asio::ip::udp::endpoint &endpoint, const std::array<char, 2048> &buffer, size_t size);
        void handleConnect(const asio::ip::udp::endpoint &endpoint, const std::array<char, 2048> &buffer, size_t size);
        void sendMessageToAllClients(const std::string& message, const asio::ip::udp::endpoint& sender);
};

#endif //R_TYPE_SERVER_HPP
