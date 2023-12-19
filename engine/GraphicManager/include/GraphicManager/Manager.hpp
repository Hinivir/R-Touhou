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
#include "SharedLibraryLoader/SpecializedLoader.hpp"

namespace GraphicManager {

class Manager : public SharedLibraryLoader::SpecializedLoader<Graphic::GraphicInstance>
{
};

//using Manager = SharedLibraryLoader::SpecializedLoader<Graphic::GraphicInstance>;

}
