/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** INetwork.hpp
*/

#ifndef INETWORK_HPP
#define INETWORK_HPP

#include <string>

class INetwork
{
public:
    virtual ~INetwork() {}

    virtual bool isConnected() = 0;

    virtual void receiveMessage(bool async) = 0;

    virtual void handleMessage() = 0;
    virtual void handleMessageString() = 0;
    virtual void handleMessageSetup() = 0;
    virtual void handleMessageGame() = 0;

    virtual void commandConnect() = 0;
    virtual void commandDisconnect() = 0;
    virtual void commandError() = 0;
    virtual void commandReady() = 0;
    virtual void commandFull() = 0;
    virtual void commandClientDisconnect() = 0;
    virtual void commandStartGame() = 0;

    virtual void handleGame() = 0;
};

#endif
