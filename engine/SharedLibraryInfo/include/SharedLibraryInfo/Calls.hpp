/*
** EPITECH PROJECT, 2023
** engine/SharedLibraryInfo/include/SharedLibraryInfo/Calls.hpp
** File description:
** -
*/

/// @file
/// @brief Function types used by shared libraries

#pragma once

#include <string>
#include "SharedLibraryInfo/Info.hpp"

#define SHARED_LIBRARY_INFO_CALLS_DEFAULT "entryPoint"
#define SHARED_LIBRARY_INFO_CALLS_INFO "info"

namespace SharedLibraryInfo { namespace Calls {

using Default = void (*)();
using Info = SharedLibraryInfo::Info (*)();

}}
