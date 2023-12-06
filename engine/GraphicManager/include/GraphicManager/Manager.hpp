/*
** EPITECH PROJECT, 2023
** engine/GraphicManager/include/Manager.hpp
** File description:
** -
*/

/// @file
/// @brief Class used for managing graphic libraries loaded dynamically

#pragma once
#include <iostream>
#include "Graphic/GraphicInstance.hpp"
#include "SharedLibraryLoader/Loader.hpp"

namespace GraphicManager {

class Manager : public SharedLibraryLoader::Loader
{

// PUBLIC ATTRIBUTES
public:

// Constructors

    /// @brief Constructor
    /// @param filepath (optional) Path of the shared library
    Manager(void);
    /// @brief Constructor
    /// @param filepath (optional) Path of the shared library
    Manager(std::string const &filepath);

// Functions

    /// @brief Initialize the value of `instance` based on `callEntryPoint`
    /// @return True, of false if nothing was changed
    bool instantiate(void);

// Variables
    Graphic::GraphicInstance instance;

};

}
