cmake_minimum_required(VERSION 3.5.X)

set(CMAKE_CXX_STANDARD 20)

set(SFML_BINARY_NAME "L-Type-Library-SFML")

project(${SFML_BINARY_NAME} LANGUAGES CXX)

set(SFML_FOLDER libraries/SFML)

set(SFML_INCLUDE
                ${SFML_FOLDER}/include
                engine/Graphic/include
                engine/GraphicClientProtocol/include
                engine/Input/include
                engine/LType/include
                engine/SharedLibraryInfo/include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${SFML_FOLDER})
set(CMAKE_RELEASE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${SFML_FOLDER})

include(libraries/SFML/SFMLSrc.cmake)
include(engine/Graphic/GraphicSrc.cmake)
include(engine/GraphicClientProtocol/GraphicClientProtocolSrc.cmake)
include(engine/Input/InputSrc.cmake)
include(engine/LType/LTypeSrc.cmake)

set(SRC
        ${GRAPHIC_SRC}
        ${GRAPHIC_CLIENT_PROTOCOL_SRC}
        ${INPUT_SRC}
        ${LTYPE_SRC})

add_library(${SFML_BINARY_NAME} SHARED ${SFML_SRC})

target_sources(${SFML_BINARY_NAME} PUBLIC ${SRC})

target_include_directories(${SFML_BINARY_NAME} PUBLIC ${SFML_INCLUDE})

set_target_properties(${SFML_BINARY_NAME} PROPERTIES PREFIX "")

target_link_libraries(${SFML_BINARY_NAME} PRIVATE sfml-graphics)
