cmake_minimum_required(VERSION 3.27.7)

set(CMAKE_CXX_STANDARD 20)

set(PROJECT_NAME "R-Touhou")

include(FetchContent)
FetchContent_Declare(SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG        2.5.1
)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(SDL2
  GIT_REPOSITORY https://github.com/libsdl-org/SDL
  GIT_TAG        release-2.28.5
)
FetchContent_MakeAvailable(SDL2)

FetchContent_Declare(
  asiocmake
  GIT_REPOSITORY "https://github.com/OlivierLDff/asio.cmake"
  GIT_TAG        "main"
)
FetchContent_MakeAvailable(asiocmake)

project(${PROJECT_NAME} LANGUAGES CXX)

include(engine/ClientManager/ClientManager.cmake)
include(engine/GraphicManager/GraphicManager.cmake)
include(engine/ServerManager/ServerManager.cmake)
