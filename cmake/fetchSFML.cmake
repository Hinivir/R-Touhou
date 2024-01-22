#
# EPITECH PROJECT, 2023
# R-Touhou 
# File description:
# Fetch SFML using FetchContent 
#

cmake_minimum_required(VERSION 3.5.X)

find_package(SFML 2.6.0 QUIET)
include(FetchContent)
FetchContent_Declare(SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG        2.6.x
)
FetchContent_MakeAvailable(SFML)
