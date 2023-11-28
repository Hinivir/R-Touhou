/*
** EPITECH PROJECT, 2023
** engine/SharedLibraryLoader/src/Loader.cpp
** File description:
** -
*/

#include <dlfcn.h>
#include "SharedLibraryLoader/Exception.hpp"
#include "SharedLibraryLoader/Loader.hpp"

// LOADING AND UNLOADING

void SharedLibraryLoader::Loader::load(std::string const &filepath)
{
    unload();
    library = dlopen(filepath.c_str(), RTLD_NOW);
    if (!library) {
        unload();
        throw SharedLibraryLoader::Exception::DLFcn(std::string(SHARED_LIBRARY_LOADER_EXCEPTION_DLFCN_WHAT) + ": DLOpen returned '" + std::string(dlerror()) + "'");
    }
    entryPoint = dlsym(library, "entryPoint");
    if (!entryPoint) {
        unload();
        throw SharedLibraryLoader::Exception::DLFcn(std::string(SHARED_LIBRARY_LOADER_EXCEPTION_DLFCN_WHAT) + ": DLSym returned '" + std::string(dlerror()) + "'");
    }
    libraryPath = filepath;
}

void SharedLibraryLoader::Loader::unload(void)
{
    entryPoint = nullptr;
    if (library) {
        dlclose(library);
        library = nullptr;
    }
    libraryPath = "";
}

// OTHERS

bool SharedLibraryLoader::Loader::isLoaded(void) const
{
    return (library != nullptr && entryPoint != nullptr);
}
