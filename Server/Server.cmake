cmake_minimum_required(VERSION 3.25.X)

set(CMAKE_CXX_STANDARD 20)

set(SERVER_BINARY_NAME "L-Type-Server")

project(${SERVER_BINARY_NAME} LANGUAGES CXX)

set(SERVER_FOLDER Server)

set(INCLUDE ${CMAKE_SOURCE_DIR}/ecs ${SERVER_FOLDER}/include)

set(SERVER_INCLUDE ${INCLUDE})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${SERVER_FOLDER})

include(${SERVER_FOLDER}/ServerSrc.cmake)

add_executable(${SERVER_BINARY_NAME} ${SRC})

target_link_libraries(${SERVER_BINARY_NAME} PRIVATE sfml-graphics sfml-window sfml-system)
target_link_libraries(${SERVER_BINARY_NAME} PRIVATE asio)
target_include_directories(${SERVER_BINARY_NAME} PUBLIC ${SERVER_INCLUDE})


if (DEFINED INSTALL)
  install(TARGETS ${SERVER_BINARY_NAME} RUNTIME DESTINATION BIN)
endif (DEFINED INSTALL)
