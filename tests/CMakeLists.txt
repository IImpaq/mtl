cmake_minimum_required(VERSION 3.21)
project(tests)

message("Start making project: " ${PROJECT_NAME})

message(" - Defining basic variables...")
set(CMAKE_CXX_STANDARD 23)

message(" - Setting up make directories...")
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}/)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/)

message(" - Scanning for source files...")
file(GLOB_RECURSE SOURCES
        ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/src/*.cpp
        ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/src/*.hpp)

message(" - Creating static library...")
add_executable(${PROJECT_NAME} ${SOURCES})

# Including external libraries
target_include_directories(${PROJECT_NAME} PUBLIC ../ntl/src/)
target_link_libraries(${PROJECT_NAME} ntl)

message("End making project: " ${PROJECT_NAME})