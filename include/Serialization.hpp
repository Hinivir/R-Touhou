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
#include <array>
#include <SFML/Window/Keyboard.hpp>
#include "ANetwork.hpp"

std::istream& operator>>(std::istream& is, std::vector<std::pair<float, float>>& pos);
std::ostream &operator<<(std::ostream &os, const std::vector<std::pair<float, float>> &pos);

struct positionMessage {
    int id;
    float x;
    float y;

    friend std::ostream &operator<<(std::ostream &os, const positionMessage &message) {
        os << message.id << " " << message.x << " " << message.y;
        return os;
    }
    friend std::istream &operator>>(std::istream &is, positionMessage &message) {
        is >> message.id >> message.x >> message.y;
        if (is.fail()) {
            throw std::runtime_error("Error while deserializing positionMessage");
        }
        return is;
    }
};

struct garbageMessage {
    int id;

    friend std::ostream &operator<<(std::ostream &os, const garbageMessage &message) {
        os << message.id;
        return os;
    }
    friend std::istream &operator>>(std::istream &is, garbageMessage &message) {
        is >> message.id;
        if (is.fail()) {
            throw std::runtime_error("Error while deserializing garbageMessage");
        }
        return is;
    }
};

inline std::ostream &operator<<(std::ostream &os, const sf::Keyboard::Key &key)
{
    os << key;
    return os;
}

inline std::istream &operator>>(std::istream &is, sf::Keyboard::Key &key)
{
    int k;
    is >> k;
    key = static_cast<sf::Keyboard::Key>(k);
    if (is.fail()) {
        throw std::runtime_error("Error while deserializing sf::Keyboard::Key");
    }
    return is;
}

struct inputMessage {
    std::size_t id;
    sf::Keyboard::Key key;

    friend std::ostream &operator<<(std::ostream &os, const inputMessage &message) {
        os << message.id << " " << message.key;
        return os;
    }
    friend std::istream &operator>>(std::istream &is, inputMessage &message) {
        is >> message.id >> message.key;
        if (is.fail()) {
            throw std::runtime_error("Error while deserializing inputMessage");
        }
        return is;
    }
};

struct shootMessage {
    float shootX;
    float shootY;
    std::size_t id;

    friend std::ostream &operator<<(std::ostream &os, const shootMessage &message) {
        os << message.shootX << " " << message.shootY << " " << message.id;
        return os;
    }
    friend std::istream &operator>>(std::istream &is, shootMessage &message) {
        is >> message.shootX >> message.shootY >> message.id;
        if (is.fail()) {
            throw std::runtime_error("Error while deserializing shootMessage");
        }
        return is;
    }
};

template <typename T>
void serialize(T& data, std::array<char, 2048>& buffer) {
    std::ostringstream os;
    os << data;
    std::size_t size = os.str().copy(buffer.data(), buffer.size());
    buffer[size] = '\0';
}

template <typename T>
T deserialize(std::array<char, 2048>& buffer) {
    T data;
    std::istringstream is(std::string(buffer.data()));
    is >> data;
    return data;
}

#endif /* !SERIALIZATION_HPP_ */
