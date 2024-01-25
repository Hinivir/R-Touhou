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

class Server : protected ANetwork
{
  private:
    std::size_t _port;
    std::size_t maxPlayers = 4;
    std::size_t playerNumber = 0;
    std::vector<asio::ip::udp::endpoint> clients;
    std::map<asio::ip::udp::endpoint, int> playerNumberMap;

  public:
    Server(const std::string &ip, const std::string &port);
    ~Server();
    void manageServer();
    void verifConnected();
    void sendMessageToAllClients(const std::string &message);
    bool handleCommand(std::array<char, 2048> buffer, size_t size);
    template <typename messageTemplate>
    void handleMessageClient(messageTemplate &message)
    {
    }

    // command functions herited from ANetwork
    void commandConnect();
    void commandDisconnect();
    void commandError();
    void commandReady();
    void commandFull();

    void manageMessage(const std::type_info &info);
};

#endif // R_TYPE_SERVER_HPP
