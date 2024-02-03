#
# EPITECH PROJECT, 2023
# R-Touhou 
# File description:
# Fetch Asio using FetchContent 
#

cmake_minimum_required(VERSION 3.5.X)

find_package(Asio QUIET)
if (ASIO_FOUND)
  message("Asio Found")
else()
  include(FetchContent)
  FetchContent_Declare(asiocmake
    GIT_REPOSITORY https://github.com/OlivierLDff/asio.cmake.git
    GIT_TAG       v1.2.0 
  )
  FetchContent_MakeAvailable(asiocmake)
endif()
