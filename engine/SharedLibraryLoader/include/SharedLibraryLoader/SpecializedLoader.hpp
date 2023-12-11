/*
** EPITECH PROJECT, 2023
** engine/SharedLibraryLoader/include/SpecializedLoader.hpp
** File description:
** -
*/

/// @file
/// @brief Class inherting from Loader and using templates to generate instances of a type

#pragma once
#include "SharedLibraryLoader/Loader.hpp"

namespace SharedLibraryLoader {

template<class T_INSTANCE>
class SpecializedLoader : public SharedLibraryLoader::Loader
{

// PUBLIC ATTRIBUTES
public:

// Constructors

    /// @brief Constructor
    /// @param filepath (optional) Path of the shared library
    SpecializedLoader(void) {type = SharedLibraryInfo::InfoType::LIBRARY;}
    /// @brief Constructor
    /// @param filepath (optional) Path of the shared library
    SpecializedLoader(std::string const &filepath) {SpecializedLoader(); load(filepath);}

// Functions

    /// @brief Initialize the value of `instance` based on `callEntryPoint`
    /// @return True, of false if nothing was changed
    bool instantiate(void) {if (!callEntryPoint) return false; instance = (reinterpret_cast<T_INSTANCE (*)()>(callEntryPoint))(); return true;}

// Variables
    T_INSTANCE instance;

};

}
