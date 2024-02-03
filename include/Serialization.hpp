/*
** EPITECH PROJECT, 2024
** R-Touhou
** File description:
** Serialization
*/

#ifndef SERIALIZATION_HPP_
#define SERIALIZATION_HPP_

#include <sstream>
#include <vector>
#include <SFML/Window/Keyboard.hpp>

std::ostream &operator<<(std::ostream &os, std::vector<std::pair<float, float>> &pos);
std::istream &operator>>(std::istream &is, std::vector<std::pair<float, float>> &pos);

std::ostream &operator<<(std::ostream &os, sf::Keyboard::Key &key);
std::istream &operator>>(std::istream &is, sf::Keyboard::Key &key);

struct positionMessage
{
    char type = 'p';
    int id;
    float x;
    float y;

    friend std::ostream &operator<<(std::ostream &os, const positionMessage &message)
    {
        os << message.type << " " << message.id << " " << message.x << " " << message.y;
        return os;
    }
    friend std::istream &operator>>(std::istream &is, positionMessage &message)
    {
        is >> message.type >> message.id >> message.x >> message.y;
        if (is.fail() || message.type != 'p') {
            throw std::runtime_error("Error while deserializing positionMessage");
        }
        return is;
    }
};

struct bulletMessage
{
    char type = 'b';
    float x;
    float y;

    friend std::ostream &operator<<(std::ostream &os, const bulletMessage &message)
    {
        os << message.type << " " << message.x << " " << message.y;
        return os;
    }
    friend std::istream &operator>>(std::istream &is, bulletMessage &message)
    {
        is >> message.type >> message.x >> message.y;
        if (is.fail() || message.type != 'b') {
            throw std::runtime_error("Error while deserializing bulletMessage");
        }
        return is;
    }
};

struct inputMessage
{
    char type = 'i';
    std::size_t id;
    sf::Keyboard::Key key;

    friend std::ostream &operator<<(std::ostream &os, const inputMessage &message)
    {
        os << message.type << " " << message.id << " " << message.key;
        return os;
    }
    friend std::istream &operator>>(std::istream &is, inputMessage &message)
    {
        is >> message.type >> message.id >> message.key;
        if (is.fail() || message.type != 'i') {
            throw std::runtime_error("Error while deserializing inputMessage");
        }
        return is;
    }
};

struct garbageMessage
{
    char type = 'g';
    int id;

    friend std::ostream &operator<<(std::ostream &os, const garbageMessage &message)
    {
        os << message.type << " " << message.id;
        return os;
    }
    friend std::istream &operator>>(std::istream &is, garbageMessage &message)
    {
        is >> message.type >> message.id;
        if (is.fail() || message.type != 'g') {
            throw std::runtime_error("Error while deserializing garbageMessage");
        }
        return is;
    }
};

#endif /* !SERIALIZATION_HPP_ */
