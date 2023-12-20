/*
** EPITECH PROJECT, 2023
** engine/SharedLibraryLoader/include/SpecializedLoader.hpp
** File description:
** -
*/

/// @file
/// @brief Class inherting from Loader and using templates to generate instances of a type

#pragma once
#include "GraphicClientProtocol/Layer/StackMap.hpp"
#include "Input/InputMapRef.hpp"
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

    /// @brief Instantiate `callEntryPoint` inside of `instance`
    /// @param stackMap StackMap put inside of `instance`
    /// @param inputMap InputMap put inside of `instance`
    /// @return `true`, of `false` if a problem is encountered
    bool instantiate(GraphicClientProtocol::Layer::StackMapRef const &stackMap, Input::InputMapRef const &inputMap)
    {
        if (!callEntryPoint)
            return false;
        instance = (reinterpret_cast<T_INSTANCE (*)()>(callEntryPoint))();
        if (!instance)
            return false;
        instance->setStackMap(stackMap);
        instance->setInputMap(inputMap);
        return true;
    }

// Variables
    T_INSTANCE instance;

};

}
