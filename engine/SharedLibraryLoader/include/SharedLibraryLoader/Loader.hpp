/*
** EPITECH PROJECT, 2023
** engine/SharedLibraryLoader/include/Loader.hpp
** File description:
** -
*/

/// @file
/// @brief Class used for loading shared libraries dynamically

#include <string>

namespace SharedLibraryLoader {

class Loader {

// PUBLIC ATTRIBUTES //
public:

// Functions

    // Loading and Unloading shared libraries

    /// @brief Loads a shared library into `library`
    /// @param filepath Path of the shared library
    void load(std::string const &filepath);
    /// @brief Unloads the shared library contained inside of `library`
    void unload(void);

    // Others

    /// @brief Checks if `library` is loaded
    /// @return True, or False if `library` is NULL
    bool isLoaded(void) const;

// Variables
    void *entryPoint = nullptr;
    void *library = nullptr;
    std::string libraryPath = "";

};

}
