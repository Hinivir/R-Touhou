/*
** EPITECH PROJECT, 2024
** R-Touhou
** File description:
** operator
*/

#ifndef OPERATOR_HPP
#define OPERATOR_HPP

// operators.hpp
#include <vector>
#include <utility>
#include <iostream>
#include <sstream>

std::ostream& operator<<(std::ostream& os, const std::vector<std::pair<float, float>>& pos);
std::ostream &operator<<(std::ostream &os, const std::vector<std::pair<float, float>> &pos);
std::istream& operator>>(std::istream& is, std::vector<std::pair<float, float>>& pos);

#endif //OPERATOR_HPP
