/*
** EPITECH PROJECT, 2023
** app/Instance/src/Main.cpp
** File description:
** -
*/

#include <iostream>
#include <SharedLibraryInfo/Info.hpp>
#include <SharedLibraryLoader/Loader.hpp>

int main(void)
{
    SharedLibraryInfo::Info info = {
        SharedLibraryInfo::InfoType::UNDEFINED,
        "Unknown",
        "1.0"
    };
    SharedLibraryLoader::Loader loader;

    std::cout << "Hello from L-Type" << std::endl;
    std::cout << info.name << std::endl;
    return 0;
}
