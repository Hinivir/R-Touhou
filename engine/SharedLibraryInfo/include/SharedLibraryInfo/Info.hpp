/*
** EPITECH PROJECT, 2023
** engine/SharedLibraryInfo/include/SharedLibraryInfo/Info.hpp
** File description:
** -
*/

/// @file
/// @brief Structure used when loading shared libraries

#pragma once

#include <string>

namespace SharedLibraryInfo {

enum class InfoType {
    UNDEFINED,
    GAME,
    LIBRARY,
    TOTAL,
};

using Info = struct Info_s {
    SharedLibraryInfo::InfoType type;
    std::string name;
    std::string version;
};

}
