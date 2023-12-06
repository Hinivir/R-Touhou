/*
** EPITECH PROJECT, 2023
** R-Touhou
** File description:
** server_init.cpp
*/

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int const argc, char const * const * const argv) {
    std::size_t port = 0;
    std::size_t serverSocket = 0;
    std::size_t clientSocket = 0;
    sockaddr_in serverAddress;
    std::string ip = "";

    if (argc != 2) {
        std::cerr << "Usage: ./server -h" << std::endl;
        return 84;
    }

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Erreur lors de la création du socket." << std::endl;
        return 84;
    }
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(27015);
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Erreur lors de la liaison du socket à l'adresse demandé" << std::endl;
        close(serverSocket);
        return 84;
    }
    if (listen(serverSocket, 10) == -1) {
        std::cerr << "Erreur lors de la connexions" << std::endl;
        close(serverSocket);
        return 84;
    }
    while (1) {
        clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket == -1) {
            std::cerr << "Erreur lors de l'acceptation du client" << std::endl;
            close(serverSocket);
            return 84;
        }
        close(clientSocket);
    }
    close(serverSocket);
    return 0;
}
