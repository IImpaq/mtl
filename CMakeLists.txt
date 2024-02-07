#######################
# BASIC PROJECT SETUP #
#######################

cmake_minimum_required(VERSION 3.21)
project(ntl-root)

if(DEFINED CMAKE_TOOLCHAIN_FILE)
    include(${CMAKE_TOOLCHAIN_FILE})
endif()

message("Start making workspace: " ${PROJECT_NAME})

message(" - Defining basic variables...")
set(CMAKE_CXX_STANDARD 23)

message(" - Adding libraries to workspace...")

#################################
# INCLUDING 3RD-PARTY LIBRARIES #
#################################

# Adding Catch2
find_package(Catch2 CONFIG REQUIRED)

########################################
# INCLUDING LIBRARY AND OTHER PROJECTS #
########################################

message(" - Adding projects to workspace...")
# Adding subprojects
add_subdirectory(ntl)
add_subdirectory(tests)
add_subdirectory(demo)

message("End making workspace: " ${PROJECT_NAME})
