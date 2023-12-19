/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Client.cpp
*/

#include "../include/Client.hpp"
#include <iostream>
#include <map>
#include <string>

Client::Client(asio::io_context& io_context, const std::string& server_ip, std::size_t server_port)
    : socket_(io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), 0)),
        server_endpoint_(asio::ip::address::from_string(server_ip), server_port) {}

void Client::sendMessage(const std::string& message) {
    socket_.send_to(asio::buffer(message), server_endpoint_);
}

