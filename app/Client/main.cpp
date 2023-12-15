/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** main.cpp
*/

#include "include/Client.hpp"

int main(void)
{
    Client client = Client("tmp", 8080);
    client.runClient();
    return 0;
}
