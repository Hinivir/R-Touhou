cmake_minimum_required(VERSION 3.27.7)

set(CMAKE_CXX_STANDARD 20)

set(SFML_BINARY_NAME "L-Type-Library-SFML")

project(${SFML_BINARY_NAME} LANGUAGES CXX)

set(INCLUDE_SFML)

function(SFML_ADD_DIRECTORY_NO_SRC ADDED_DIRECTORY)
    target_include_directories(${SFML_BINARY_NAME} PUBLIC ${ADDED_DIRECTORY}/include)
endfunction()

function(SFML_ADD_DIRECTORY_BASE ADDED_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${ADDED_DIRECTORY})
    file(READ ${ADDED_DIRECTORY}/src.txt SOURCE_FILES_CONTENT_SFML)
    string(REPLACE "\n" ";" SOURCE_FILES_SFML ${SOURCE_FILES_CONTENT_SFML})
    add_library(${SFML_BINARY_NAME} SHARED ${SOURCE_FILES_SFML})
    sfml_add_directory_no_src(${ADDED_DIRECTORY})
endfunction()

function(SFML_ADD_DIRECTORY ADDED_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${ADDED_DIRECTORY})
    file(READ ${ADDED_DIRECTORY}/src.txt SOURCE_FILES_CONTENT_SFML)
    string(REPLACE "\n" ";" SOURCE_FILES_SFML ${SOURCE_FILES_CONTENT_SFML})
    target_sources(${SFML_BINARY_NAME} PUBLIC ${SOURCE_FILES_SFML})
    sfml_add_directory_no_src(${ADDED_DIRECTORY})
endfunction()

# BASE
sfml_add_directory_base(libraries/SFML)
# Directories WITH sources
sfml_add_directory(engine/Graphic)
sfml_add_directory(engine/Input)
# Directories WITHOUT sources
sfml_add_directory_no_src(engine/SharedLibraryInfo)

set_target_properties(${SFML_BINARY_NAME} PROPERTIES PREFIX "")

target_link_libraries(${SFML_BINARY_NAME} PRIVATE sfml-graphics)
