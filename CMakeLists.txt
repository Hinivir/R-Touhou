#
# EPITECH PROJECT, 2023
# r-type-mirror
# File description:
# CMakeLists.txt
#

cmake_minimum_required(VERSION 3.5.X)

set(CMAKE_CXX_STANDARD 20)

set(PROJECT_NAME "L-Type")

set(CPACK_PACKAGE_NAME "L-Type")

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
include(app/Server/Server.cmake)
include(games/guideExample/Build.cmake)
include(games/R-Type/R-Type.cmake)

if (DEFINED INSTALL)

  if (WIN32)
    set (CPACK_GENERATOR "NSIS;ZIP" CACHE STRING "Semicolon separated list of generators")
  else ()
    set (CPACK_GENERATOR "STGZ;ZIP" CACHE STRING "Semicolon separated list of generators")
  endif ()

  include (CPack)

endif()
