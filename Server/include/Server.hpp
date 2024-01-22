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
        asio::ip::udp::endpoint _endpoint;
        std::vector<asio::ip::udp::endpoint> clients;
        std::map<asio::ip::udp::endpoint, int> playerNumberMap;

    public:
        static const std::map<std::string, std::function<void(Server&, const asio::ip::udp::endpoint&, const std::array<char, 2048>&, size_t)>> commandHandler;
        Server(const std::string &ip, const std::string &port);
        ~Server();
        void acceptClients();
        void verifConnected();
        void manageMessage();
        void handleConnect(const asio::ip::udp::endpoint &endpoint, const std::array<char, 2048> &buffer, size_t size);
        void sendMessageToAllClients(const std::string& message, const asio::ip::udp::endpoint& sender);
};

#endif //R_TYPE_SERVER_HPP
