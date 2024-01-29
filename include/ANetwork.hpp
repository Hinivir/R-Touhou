/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** ANetwork.hpp
*/

#ifndef ANETWORK_HPP
#define ANETWORK_HPP

#include <iostream>
#include <array>

#include <asio.hpp>
#include "Components/Position.hpp"
#include <map>

#define CONNECTED "101: You are connected!\n"
#define DISCONNECTED "103: You are disconnected!\n"
#define ERROR_MSG "102: Error sending confirmation message to client!\n"
#define READY "104: You are ready!\n"
#define SERVER_FULL "105: Server is full!\n"
#define NEW_CLIENT "106: New client connected!\n"
#define CLIENT_DISCONNECTED "107: Client disconnected!\n"

template <typename T>
void serialize(const T& data, std::array<char, 2048>& buffer) {
    std::ostringstream os;
    os << data;
    std::size_t size = os.str().copy(buffer.data(), buffer.size());
    buffer[size] = '\0';
}

template <typename T>
T deserialize(const std::array<char, 2048>& buffer) {
    T data;
    std::istringstream is(std::string(buffer.data()));
    is >> data;
    return data;
}

template <typename senderMessage>
struct inGame_message
{
    std::size_t index;
    senderMessage message;
};

struct outGame_message
{
    asio::ip::udp::endpoint senderEndpoint;
    std::string &message;
};

class ANetwork
{
  protected:
    std::array<char, 2048> buffer;
    std::string ip;
    std::string port;
    std::size_t bytesReceived;
    asio::io_context ioContext;
    asio::ip::udp::socket socket;
    asio::ip::udp::endpoint senderEndpoint;
    std::size_t playerNumber = 0;
    bool running = true;
    bool isInChat = true;

    const std::map<std::string, std::function<void(ANetwork &)>> clientCommandHandler = {
        {CONNECTED, &ANetwork::commandConnect},
        {DISCONNECTED, &ANetwork::commandDisconnect},
        {ERROR_MSG, &ANetwork::commandError},
        {READY, &ANetwork::commandReady},
        {SERVER_FULL, &ANetwork::commandFull},
        {CLIENT_DISCONNECTED, &ANetwork::commandClientDisconnect}
    };

    const std::map<std::string, std::function<void(ANetwork &)>> serverCommandHandler = {
        {"connect\n", &ANetwork::commandConnect},
        {"disconnect\n", &ANetwork::commandDisconnect},
        {"ready\n", &ANetwork::commandReady},
    };

  public:
    ANetwork(const std::string ip, const std::string port) : ioContext(), socket(ioContext)
    {
        this->ip = ip;
        this->port = port;
    }

    bool isConnected() { return running; }

    template <typename messageTemplate>
    void sendMessage(const messageTemplate &message, const asio::ip::udp::endpoint &receiverEndpoint, bool async)
    {
        if (async) {
            socket.async_send_to(asio::buffer(message), receiverEndpoint,
                [](const asio::error_code &error, std::size_t bytes_transferred) {
                    if (error) {
                        std::cerr << "ERROR: " << error.message() << std::endl;
                        return;
                    }
                });
        } else {
            socket.send_to(asio::buffer(message), receiverEndpoint);
        }
    }

    void receiveMessage(bool async)
    {
        buffer.fill(0);
        if (async) {
            socket.async_receive_from(asio::buffer(buffer), senderEndpoint,
                [this](const asio::error_code &error, std::size_t bytes_transferred) {
                    if (!error) {
                        bytesReceived = bytes_transferred;
                        handleMessage();
                        receiveMessage(true);
                    } else {
                        std::cerr << "ERROR: " << error.message() << std::endl;
                    }
                });
        } else {
            bytesReceived = socket.receive_from(asio::buffer(buffer), senderEndpoint);
            if (isInChat)
                handleMessage();
        }
    }

    void handleMessage()
    {
        if (isInChat) {
            handleMessageString();
        } else
            std::cout << "message is not a string" << std::endl;
    }
    virtual void handleMessageString() = 0;

    // all these functions will be virtual in the future so we can override them
    virtual void commandConnect() = 0;
    virtual void commandDisconnect() = 0;
    virtual void commandError() = 0;
    virtual void commandReady() = 0;
    virtual void commandFull() = 0;
    virtual void commandClientDisconnect() = 0;

    virtual void manageMessage(const std::type_info &type) = 0;//to be deleted
    virtual void runGame() = 0;

    asio::io_context &getIoContext() { return this->ioContext; }
    std::array<char, 2048> getBuffer() { return this->buffer; }
};
#endif
