/*
** EPITECH PROJECT, 2023
** app/Instance/src/Main.cpp
** File description:
** -
*/

#include <exception>
#include <iostream>
#include <GraphicManager/Manager.hpp>
#include <GraphicClientProtocol/Layer/StackMap.hpp>
#include <Input/InputMapRef.hpp>
#include <SharedLibraryInfo/Info.hpp>
#include <SharedLibraryLoader/Exception.hpp>

#define OUTPUT_REGULAR  0
#define OUTPUT_ERROR    84

int main(void)
{
    SharedLibraryInfo::Info info;
    GraphicManager::Manager loader;
    GraphicClientProtocol::Layer::StackMapRef stackMap;
    Input::InputMapRef inputMap;

    try {
        loader.load("./L-Type-Library-SFML.so");
    } catch (SharedLibraryLoader::Exception::DLFcn &e) {
        std::cerr << e.what() << std::endl;
    } catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
    }
    if (loader.isLoaded() && loader.callInfo) {
        info = loader.callInfo();
        std::cout << info.name << " - " << info.version << std::endl;
    } else {
        std::cerr << "Loader has not been loaded correctly" << std::endl;
    }
    if (!loader.instantiate())
        return OUTPUT_ERROR;
    inputMap = Input::createInputMapRef();
    stackMap = GraphicClientProtocol::Layer::createStackMapRef();
    stackMap->insert({GRAPHIC_WINDOWID_DEFAULT, GraphicClientProtocol::Layer::Stack()});
    auto defaultWindowInputMap = stackMap->find(GRAPHIC_WINDOWID_DEFAULT);
    if (defaultWindowInputMap != stackMap->end())
        defaultWindowInputMap->second.push_back(GraphicClientProtocol::Layer::StackElement(GraphicClientProtocol::Layer::Color(GraphicClientProtocol::Color())));
    loader.instance->openWindow();
    loader.instance->setInputMap(inputMap);
    loader.instance->setStackMap(stackMap);
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
