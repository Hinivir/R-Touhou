#
# EPITECH PROJECT, 2023
# r-type-mirror
# File description:
# CMakeLists.txt
#

cmake_minimum_required(VERSION 3.27.5)

set(CMAKE_CXX_STANDARD 20)

set(PROJECT_NAME "L-Type")
#[[
include(FetchContent)
FetchContent_Declare(SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG        2.5.1
)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(
  asiocmake
  GIT_REPOSITORY "https://github.com/OlivierLDff/asio.cmake"
  GIT_TAG        "main"
)
FetchContent_MakeAvailable(asiocmake)
]]
project(${PROJECT_NAME} LANGUAGES CXX)

include(app/Instance/Instance.cmake)
include(app/ServerManager/ServerManager.cmake)
include(libraries/SFML/SFML.cmake)
include(games/RTouhou/RTouhou.cmake)
