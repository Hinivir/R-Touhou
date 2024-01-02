cmake_minimum_required(VERSION 3.5.X)

set(CMAKE_CXX_STANDARD 20)

set(L_TYPE_BINARY_NAME "L-Type")

project(${L_TYPE_BINARY_NAME} LANGUAGES CXX)

set(INSTANCE_FOLDER app/Instance)

set(INSTANCE_INCLUDE
                        app/Instance/include
                        engine/SharedLibraryInfo/include
                        engine/SharedLibraryLoader/include
                        engine/Game/include
                        engine/GameManager/include
                        engine/Graphic/include
                        engine/GraphicClientProtocol/include
                        engine/GraphicManager/include
                        engine/Input/include
                        engine/LType/include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${INSTANCE_FOLDER})
set(CMAKE_RELEASE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${INSTANCE_FOLDER})

include(app/Instance/InstanceSrc.cmake)
include(engine/Game/GameSrc.cmake)
include(engine/GameManager/GameManagerSrc.cmake)
include(engine/Graphic/GraphicSrc.cmake)
include(engine/GraphicClientProtocol/GraphicClientProtocolSrc.cmake)
include(engine/GraphicManager/GraphicManagerSrc.cmake)
include(engine/Input/InputSrc.cmake)
include(engine/LType/LTypeSrc.cmake)
include(engine/SharedLibraryLoader/SharedLiBraryLoaderSrc.cmake)

set(SRC
    ${SRC_INSTANCE}
    ${SRC_GAME}
    ${SRC_GAME_MANAGER}
    ${SRC_GRAPHIC}
    ${SRC_GRAPHIC_CLIENT_PROTOCOL}
    ${SRC_GRAPHIC_MANAGER}
    ${SRC_INPUT}
    ${SRC_L_TYPE}
    ${SRC_SHARED_LIBRARY_LOADER})

add_executable(${L_TYPE_BINARY_NAME} ${SRC})

target_include_directories(${L_TYPE_BINARY_NAME} PUBLIC ${INSTANCE_INCLUDE})

if(DEFINED INSTALL)
    install(TARGETS ${L_TYPE_BINARY_NAME} RUNTIME DESTINATION BIN)
endif(DEFINED INSTALL)
