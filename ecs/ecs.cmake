cmake_minimum_required(VERSION 3.5.X)

set(CMAKE_CXX_STANDARD 20)

set(PROJECT_NAME "L-Type-Bootstrap")

set(SRC
        ${CMAKE_SOURCE_DIR}/ecs/src/Main.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/ecs)

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/ecs/include)
