cmake_minimum_required(VERSION 3.27.7)

set(CMAKE_CXX_STANDARD 20)

set(PROJECT_NAME "L-Type")

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

project(${PROJECT_NAME} LANGUAGES CXX)

#include(app/Instance/Instance.cmake)
#include(app/ServerManager/ServerManager.cmake)
<<<<<<< HEAD
=======
include(app/Client/Client.cmake)
>>>>>>> 09f0b96f061dec4febeb09094666bf33ee50d739
include(app/Server/Server.cmake)
