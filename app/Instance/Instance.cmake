cmake_minimum_required(VERSION 3.27.7)

set(CMAKE_CXX_STANDARD 20)

set(L_TYPE_BINARY_NAME "L-Type")

project(${L_TYPE_BINARY_NAME} LANGUAGES CXX)

set(INCLUDE_L_TYPE)

function(L_TYPE_ADD_DIRECTORY_NO_SRC ADDED_DIRECTORY)
    target_include_directories(${L_TYPE_BINARY_NAME} PUBLIC ${ADDED_DIRECTORY}/include)
endfunction()

function(L_TYPE_ADD_DIRECTORY_BASE ADDED_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${ADDED_DIRECTORY})
    file(READ ${ADDED_DIRECTORY}/src.txt SOURCE_FILES_CONTENT_L_TYPE)
    string(REPLACE "\n" ";" SOURCE_FILES_L_TYPE ${SOURCE_FILES_CONTENT_L_TYPE})
    add_executable(${L_TYPE_BINARY_NAME} ${SOURCE_FILES_L_TYPE})
    l_type_add_directory_no_src(${ADDED_DIRECTORY})
endfunction()

function(L_TYPE_ADD_DIRECTORY ADDED_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${ADDED_DIRECTORY})
    file(READ ${ADDED_DIRECTORY}/src.txt SOURCE_FILES_CONTENT_L_TYPE)
    string(REPLACE "\n" ";" SOURCE_FILES_L_TYPE ${SOURCE_FILES_CONTENT_L_TYPE})
    target_sources(${L_TYPE_BINARY_NAME} PUBLIC ${SOURCE_FILES_L_TYPE})
    l_type_add_directory_no_src(${ADDED_DIRECTORY})
endfunction()

# BASE
l_type_add_directory_base(app/Instance)
# Directories WITH sources
l_type_add_directory(engine/Game)
l_type_add_directory(engine/GameManager)
l_type_add_directory(engine/Graphic)
l_type_add_directory(engine/GraphicClientProtocol)
l_type_add_directory(engine/GraphicManager)
l_type_add_directory(engine/Input)
l_type_add_directory(engine/SharedLibraryLoader)
# Directories WITHOUT sources
l_type_add_directory_no_src(engine/SharedLibraryInfo)
