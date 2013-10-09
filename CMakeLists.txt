cmake_minimum_required(VERSION 2.8)
project(afpgame)

# Set version information in config.h file)
set(afpgame_VERSION_MAJOR 0)
set(afpgame_VERSION_MINOR 1)

# Specify default build type
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUID_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

configure_file(
   "${PROJECT_SOURCE_DIR}/config.h.in"
   "${PROJECT_BINARY_DIR}/config.h")

include_directories("${PROJECT_BINARY_DIR}")

# Configuration options
set(SFML_STATIC_LIBRARIES FALSE CACHE BOOL "Use static SFML libraries")

# General compiler options
if (SFML_STATIC_LIBRARIES)
    add_definitions(-DSFML_STATIC)
endif()

# Add C++11 compiler flags for UNIX
if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11")
endif()

# Define sources and executable
file(GLOB_RECURSE
    source_files
    src/*
)

set(EXECUTABLE_NAME "afpgame")
add_executable(${EXECUTABLE_NAME} ${source_files})

# User needs to define SFML-path
if(WIN32 AND NOT SFML_ROOT)
    set(SFML_ROOT "" CACHE PATH "SFML top-level directory")
    message("\n-> SFML directory not found. Set SFML_ROOT to SFML's top-level path")
endif()

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2.1 REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()

if(SFML_STATIC_LIBRARIES)
    set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_DEFINITIONS "SFML_STATIC")
endif()

# Copy Media files on build
add_custom_command(TARGET ${EXECUTABLE_NAME} PRE_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Media
    $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/Media)

if(WIN32 AND NOT SFLM_STATIC_LIBRARIES)
    add_custom_command(TARGET ${EXECUTABLE_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${SFML_ROOT}/bin
        $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>)
endif()

# Install
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_BINARY_DIR})

install(DIRECTORY ${CMAKE_SOURCE_DIR}/Media
    DESTINATION ${CMAKE_BINARY_DIR}
    PATTERN "CMakeLists.txt" EXCLUDE)

# Copy necessary DLLs on windows platforms
if(WIN32 AND NOT SFML_STATIC_LIBRARIES)
    install(DIRECTORY ${SFML_ROOT}/bin
        DESTINATION ${CMAKE_BINARY_DIR}
        PATTERN "*.dll")
endif()
