cmake_minimum_required(VERSION 3.5.X)

set(CMAKE_CXX_STANDARD 20)

set(RTOUHOU_BINARY_NAME "L-Type-Game-RTouhou")

project(${RTOUHOU_BINARY_NAME} LANGUAGES CXX)

set(RTOUHOU_FOLDER games/RTouhou)

set(RTOUHOU_INCLUDE
                    games/RTouhou/include
                    engine/Game/include
                    engine/GraphicClientProtocol/include
                    engine/LType/include
                    engine/SharedLibraryInfo/include
                    engine/Input/include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${RTOUHOU_FOLDER})
set(CMAKE_RELEASE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${RTOUHOU_FOLDER})

include(games/RTouhou/RTouhouSrc.cmake)
include(engine/Game/GameSrc.cmake)
include(engine/GraphicClientProtocol/GraphicClientProtocolSrc.cmake)
include(engine/LType/LTypeSrc.cmake)
include(engine/Input/InputSrc.cmake)

set(SRC
    ${SRC_RTOUHOU}
    ${SRC_GAME}
    ${SRC_GRAPHIC_CLIENT_PROTOCOL}
    ${SRC_L_TYPE}
    ${SRC_INPUT})

add_library(${RTOUHOU_BINARY_NAME} SHARED ${SRC})

target_include_directories(${RTOUHOU_BINARY_NAME} PUBLIC ${RTOUHOU_INCLUDE})

set_target_properties(${RTOUHOU_BINARY_NAME} PROPERTIES PREFIX "")

if(DEFINED INSTALL)
    install(TARGETS ${RTOUHOU_BINARY_NAME} RUNTIME DESTINATION BIN)
endif(DEFINED INSTALL)
