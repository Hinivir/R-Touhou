/*
** EPITECH PROJECT, 2023
** engine/SharedLibraryLoader/src/Loader.cpp
** File description:
** -
*/

#include <dlfcn.h>
#include "SharedLibraryLoader/Exception.hpp"
#include "SharedLibraryLoader/Loader.hpp"

#define CHECK_UNLOAD_DLFCN(CALL_VALUE, FUNCTION_NAME) if (!CALL_VALUE) { unload(); throw SharedLibraryLoader::Exception::DLFcn(std::string(SHARED_LIBRARY_LOADER_EXCEPTION_DLFCN_WHAT) + ": " + FUNCTION_NAME + " returned '" + std::string(dlerror()) + "'"); }

// DESTRUCTOR

SharedLibraryLoader::Loader::~Loader()
{
    unload();
}
#include <iostream>
// LOADING AND UNLOADING

void SharedLibraryLoader::Loader::load(std::string const &filepath)
{
    unload();
    library = dlopen(filepath.c_str(), RTLD_NOW);
    CHECK_UNLOAD_DLFCN(library, "DLOpen");
    callEntryPoint = reinterpret_cast<SharedLibraryInfo::Calls::Default>(dlsym(library, SHARED_LIBRARY_INFO_CALLS_DEFAULT));
    CHECK_UNLOAD_DLFCN(callEntryPoint, "DLSym");
    callInfo = reinterpret_cast<SharedLibraryInfo::Calls::Info>(dlsym(library, SHARED_LIBRARY_INFO_CALLS_INFO));
    CHECK_UNLOAD_DLFCN(callInfo, "DLSym");
    libraryPath = filepath;
}

void SharedLibraryLoader::Loader::unload(void)
{
    callEntryPoint = nullptr;
    callInfo = nullptr;
    if (library) {
        dlclose(library);
        library = nullptr;
    }
    libraryPath = "";
}

// OTHERS

bool SharedLibraryLoader::Loader::isLoaded(void) const
{
    return (library != nullptr && callEntryPoint != nullptr && callInfo != nullptr);
}
