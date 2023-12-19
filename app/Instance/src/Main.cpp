/*
** EPITECH PROJECT, 2023
** app/Instance/src/Main.cpp
** File description:
** -
*/

#include <exception>
#include <iostream>
#include "GraphicManager/Manager.hpp"
#include "GraphicClientProtocol/Layer/StackMap.hpp"
#include "Input/InputMapRef.hpp"
#include "SharedLibraryInfo/Info.hpp"
#include "SharedLibraryLoader/Exception.hpp"

#define OUTPUT_REGULAR  0
#define OUTPUT_ERROR    84

#define NEW_LOAD_DYNAMIC_LIBRARY(functionName, loaderType, infoExpectedType)    \
    static bool functionName(loaderType &loader, std::string const &filepath,    \
        GraphicClientProtocol::Layer::StackMapRef const &stackMap, Input::InputMapRef const &inputMap)   \
    {   \
        SharedLibraryInfo::Info info;   \
        try {   \
            loader.load(filepath);  \
        } catch (SharedLibraryLoader::Exception::DLFcn &e) {    \
            std::cerr << e.what() << std::endl;  \
        } catch (std::exception const &e) { \
            std::cerr << e.what() << std::endl;  \
            return false;   \
        }   \
        if (loader.isLoaded() && loader.callInfo) { \
            info = loader.callInfo();   \
            if (info.type != infoExpectedType) {    \
                std::cout << "Loader couldn't load " << info.name << " (" << info.version << ") correctly because it wasn't the right type" << std::endl;   \
                return false;   \
            }   \
            std::cout << "Loading " << info.name << " - " << info.version << std::endl;  \
        } else {    \
            std::cerr << "Loader has not been loaded correctly" << std::endl;   \
            return false;   \
        }   \
        return loader.instantiate(stackMap, inputMap);  \
    }

NEW_LOAD_DYNAMIC_LIBRARY(loadGraphicLibrary, GraphicManager::Manager, SharedLibraryInfo::InfoType::LIBRARY)

int main(void)
{
    GraphicManager::Manager loader;
    GraphicClientProtocol::Layer::StackMapRef stackMap = GraphicClientProtocol::Layer::createStackMapRef();
    Input::InputMapRef inputMap = Input::createInputMapRef();

    if (!loadGraphicLibrary(loader, "./L-Type-Library-SFML.so", stackMap, inputMap))
        return OUTPUT_ERROR;
    stackMap->insert({GRAPHIC_WINDOWID_DEFAULT, GraphicClientProtocol::Layer::Stack()});
    auto defaultWindowInputMap = stackMap->find(GRAPHIC_WINDOWID_DEFAULT);
    if (defaultWindowInputMap != stackMap->end())
        defaultWindowInputMap->second.push_back(GraphicClientProtocol::Layer::StackElement(GraphicClientProtocol::Layer::Color(GraphicClientProtocol::Color())));
    loader.instance->openWindow();
    while (loader.instance->isWindowOpen()) {
        loader.instance->refreshInputMap();
        for (auto const &[windowId, window] : inputMap->window) {
            if (window.getEvent(Input::InputMapEvent::CLOSE))
                loader.instance->closeWindowId(windowId);
        }
        loader.instance->drawWindowAll();
    }
    return OUTPUT_REGULAR;
}
