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

class Server: protected ANetwork
{
    private:
        std::size_t _port;
        std::size_t maxPlayers = 4;
        std::size_t  playerNumber = 0;
        std::vector<asio::ip::udp::endpoint> clients;
        std::map<asio::ip::udp::endpoint, int> playerNumberMap;

    public:
        Server(const std::string &ip, const std::string &port);
        ~Server();
        void manageServer();
        void verifConnected();
        void manageMessage();
        void handleReady(const asio::ip::udp::endpoint &endpoint, const std::array<char, 2048> &buffer, size_t size);
        void handleConnect(const asio::ip::udp::endpoint &endpoint, const std::array<char, 2048> &buffer, size_t size);
        void sendMessageToAllClients(const std::string& message, const asio::ip::udp::endpoint& sender);
        bool handleCommand(std::array<char, 2048> buffer, size_t size);
        void handleMessageClient(std::string &message) {}
};

#endif //R_TYPE_SERVER_HPP
