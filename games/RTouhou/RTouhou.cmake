cmake_minimum_required(VERSION 3.27.7)

set(CMAKE_CXX_STANDARD 20)

set(RTOUHOU_BINARY_NAME "L-Type-Game-RTouhou")

project(${RTOUHOU_BINARY_NAME} LANGUAGES CXX)

set(INCLUDE_RTOUHOU)

function(RTOUHOU_ADD_DIRECTORY_NO_SRC ADDED_DIRECTORY)
    target_include_directories(${RTOUHOU_BINARY_NAME} PUBLIC ${ADDED_DIRECTORY}/include)
endfunction()

function(RTOUHOU_ADD_DIRECTORY_BASE ADDED_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${ADDED_DIRECTORY})
    file(READ ${ADDED_DIRECTORY}/src.txt SOURCE_FILES_CONTENT_RTOUHOU)
    string(REPLACE "\n" ";" SOURCE_FILES_RTOUHOU ${SOURCE_FILES_CONTENT_RTOUHOU})
    add_library(${RTOUHOU_BINARY_NAME} SHARED ${SOURCE_FILES_RTOUHOU})
    rtouhou_add_directory_no_src(${ADDED_DIRECTORY})
endfunction()

function(RTOUHOU_ADD_DIRECTORY ADDED_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${ADDED_DIRECTORY})
    file(READ ${ADDED_DIRECTORY}/src.txt SOURCE_FILES_CONTENT_RTOUHOU)
    string(REPLACE "\n" ";" SOURCE_FILES_RTOUHOU ${SOURCE_FILES_CONTENT_RTOUHOU})
    target_sources(${RTOUHOU_BINARY_NAME} PUBLIC ${SOURCE_FILES_RTOUHOU})
    rtouhou_add_directory_no_src(${ADDED_DIRECTORY})
endfunction()

# BASE
rtouhou_add_directory_base(games/RTouhou)
# Directories WITH sources
rtouhou_add_directory(engine/Game)
# Directories WITHOUT sources
rtouhou_add_directory_no_src(engine/SharedLibraryInfo)

set_target_properties(${RTOUHOU_BINARY_NAME} PROPERTIES PREFIX "")
