/*
** EPITECH PROJECT, 2023
** engine/SharedLibraryLoader/cpp/Exception.hpp
** File description:
** -
*/

/// @file
/// @brief Error exceptions

#pragma once

#include <exception>
#include <string>

#define EXCEPTION(NAME, WHAT) \
    class NAME : public std::exception { \
    private: std::string _msg; \
    public: NAME(void) : _msg("") {} \
    public: NAME(std::string const &msg) : _msg(msg) {} \
    public: std::string const what() \
        { if (_msg.empty()) return WHAT; return _msg; } \
    };

#define SHARED_LIBRARY_LOADER_EXCEPTION_DLFCN_WHAT "Coudln't load a shared library"

namespace SharedLibraryLoader { namespace Exception {

EXCEPTION(DLFcn, SHARED_LIBRARY_LOADER_EXCEPTION_DLFCN_WHAT)

}};
