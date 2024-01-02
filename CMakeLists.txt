#
# EPITECH PROJECT, 2023
# r-type-mirror
# File description:
# CMakeLists.txt
#

cmake_minimum_required(VERSION 3.5.X)

set(CMAKE_CXX_STANDARD 20)

set(PROJECT_NAME "L-Type")

include(FetchContent)
FetchContent_Declare(SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG        2.6.x
)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(asiocmake
  GIT_REPOSITORY https://github.com/OlivierLDff/asio.cmake.git
  GIT_TAG        main
)
FetchContent_MakeAvailable(asiocmake)

project(${PROJECT_NAME} LANGUAGES CXX)

include(app/Client/Client.cmake)
include(app/Instance/Instance.cmake)
include(app/Server/Server.cmake)
include(libraries/SFML/SFML.cmake)
include(games/RTouhou/RTouhou.cmake)
