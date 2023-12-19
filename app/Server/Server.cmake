cmake_minimum_required(VERSION 3.27.7)

set(CMAKE_CXX_STANDARD 20)

set(SERVER_BINARY_NAME "L-Type-Server")

project(${SERVER_BINARY_NAME} LANGUAGES CXX)

set(SERVER_FOLDER app/Server)

set(SERVER_INCLUDE ${SERVER_FOLDER}/include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${SERVER_FOLDER})

include(${SERVER_FOLDER}/ServerSrc.cmake)

add_executable(${SERVER_BINARY_NAME} ${SRC})

<<<<<<< HEAD
target_include_directories(${SERVER_BINARY_NAME} PUBLIC ${SERVER_INCLUDE})
=======
target_include_directories(${SERVER_BINARY_NAME} PUBLIC ${SERVER_INCLUDE})
>>>>>>> 09f0b96f061dec4febeb09094666bf33ee50d739