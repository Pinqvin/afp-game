cmake_minimum_required(VERSION 2.6)
project(afpgame)

# Set version information in config.h file)
set(afpgame_VERSION_MAJOR 0)
set(afpgame_VERSION_MINOR 1)

configure_file(
   "${PROJECT_SOURCE_DIR}/config.h.in"
   "${PROJECT_BINARY_DIR}/config.h"
  )
include_directories("${PROJECT_BINARY_DIR}")

# Define sources and executable
set(SRCS
    main.cpp
    game.cpp
)

set(EXECUTABLE_NAME "afpgame")
add_executable(${EXECUTABLE_NAME} ${SRCS})

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2.1 REQUIRED system window graphics network audio)
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})

# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)

# CPack packaging
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_VERSION_MAJOR "${afpgame_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${afpgame_VERSION_MINOR}")
include(CPack)

# Copy required files for out-of-source build
execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Media Media)
