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

include (cmake/fetchASIO.cmake)
include (cmake/fetchSFML.cmake)

project(${PROJECT_NAME} LANGUAGES CXX)

include(Client/Client.cmake)
include(Server/Server.cmake)
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
