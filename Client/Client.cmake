cmake_minimum_required(VERSION 3.5.X)

set(CMAKE_CXX_STANDARD 20)

set(CLIENT_BINARY_NAME "L-Type-Client")

project(${CLIENT_BINARY_NAME} LANGUAGES CXX)

set(CLIENT_FOLDER Client)

set(INCLUDE ${CLIENT_FOLDER}/include ${CMAKE_SOURCE_DIR}/ecs ${CMAKE_SOURCE_DIR}/include)

set(CLIENT_INCLUDE ${INCLUDE})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Client)
set(CMAKE_RELEASE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Client)

include(${CLIENT_FOLDER}/ClientSrc.cmake)

add_executable(${CLIENT_BINARY_NAME} ${CLIENT_SRC})

target_link_libraries(${CLIENT_BINARY_NAME} sfml-graphics sfml-window sfml-system)
target_link_libraries(${CLIENT_BINARY_NAME} asio)
target_include_directories(${CLIENT_BINARY_NAME} PUBLIC ${CLIENT_INCLUDE})

if (DEFINED INSTALL)
  install(TARGETS ${CLIENT_BINARY_NAME} RUNTIME DESTINATION BIN)
  install(DIRECTORY ${CMAKE_SOURCE_DIR}/games/resources DESTINATION resources)
endif (DEFINED INSTALL)
