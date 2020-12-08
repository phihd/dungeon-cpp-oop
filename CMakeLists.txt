######################################################################
# Stage 1: Initialize project
######################################################################

cmake_minimum_required(VERSION 3.10)
project(dungeon VERSION 0.1.0)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

set (CMAKE_CXX_STANDARD 17)

set(TEST_DIR test)
set(SRC_DIR src)

# Set target
add_executable(${PROJECT_NAME} ${SRC_DIR}/main.cpp)


# Make the project files available as a library
#file(GLOB DUNGEON_FILES CONFIGURE_DEPENDS "${SRC_DIR}/*.hpp" "${SRC_DIR}/*.cpp")
#add_library(DUNGEON_LIB ${DUNGEON_FILES})

######################################################################
# Stage 2: Find and use SFML
######################################################################

# Add target dependencies
# Windows: Download SFML from website, extract the content and add 
#          path to /bin to Environment Variable (PATH) 
# MacOS  : Install brew, use brew to install cmake and sfml 
# Linux  : Use apt to install cmake and sfml

find_package(SFML 2.5.1 COMPONENTS system graphics audio network REQUIRED)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio sfml-system sfml-window)

######################################################################
# Stage 3: Download and install GoogleTest
######################################################################

include(CTest)
enable_testing()


# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
#if (CMAKE_VERSION VERSION_LESS 2.8.11)
#  include_directories("${gtest_SOURCE_DIR}/include")
#endif()


######################################################################
# Stage 4: Add tests
######################################################################

# Example: Coord test
file(GLOB DUNGEON_FILES_P CONFIGURE_DEPENDS "${SRC_DIR}/Coord.hpp" "${SRC_DIR}/Coord.cpp")
add_library(DUNGEON_LIB_P ${DUNGEON_FILES_P})

add_executable(example ${TEST_DIR}/CoordTest.cpp)
target_link_libraries(example gtest_main DUNGEON_LIB_P sfml-graphics sfml-audio sfml-system sfml-window)
add_test(NAME coordtest COMMAND example)

# Add more tests here


#add_executable(example ${TEST_DIR}/test2.cpp)
#target_link_libraries(example gtest_main DUNGEON_LIB sfml-graphics sfml-audio sfml-system sfml-window)
#add_test(NAME example_test COMMAND example)