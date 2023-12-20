cmake_minimum_required(VERSION 3.27.7)

set(CMAKE_CXX_STANDARD 20)

set(CLIENT_BINARY_NAME "L-Type-Client")

project(${CLIENT_BINARY_NAME} LANGUAGES CXX)

set(CLIENT_FOLDER app/Client)

set(CLIENT_INCLUDE ${CLIENT_FOLDER}/include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${CLIENT_FOLDER})

include(${CLIENT_FOLDER}/ClientSrc.cmake)

add_executable(${CLIENT_BINARY_NAME} ${SRC})

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

target_link_libraries(${CLIENT_BINARY_NAME} sfml-graphics sfml-window sfml-system)

target_include_directories(${CLIENT_BINARY_NAME} PUBLIC ${CLIENT_INCLUDE})
