/*
** EPITECH PROJECT, 2023
** app/Instance/src/Main.cpp
** File description:
** -
*/

#include <exception>
#include <iostream>
#include <SharedLibraryInfo/Info.hpp>
#include <SharedLibraryLoader/Loader.hpp>

int main(void)
{
    SharedLibraryInfo::Info info;
    SharedLibraryLoader::Loader loader;

    std::cout << "Hello from L-Type" << std::endl;
    try {
        loader.load("./L-Type-Library-SFML.so");
    } catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
    }
    if (loader.isLoaded() && loader.callInfo) {
        info = loader.callInfo();
        std::cout << info.name << " - " << info.version << std::endl;
    } else {
        std::cerr << "loader is not Loaded" << std::endl;
    }
    return 0;
}
