# Initialize project
cmake_minimum_required(VERSION 3.0.0)
project(dungeon VERSION 0.1.0)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

# Set C++ standard, change this if you wish
set (CMAKE_CXX_STANDARD 14)

# Set target
add_executable(${PROJECT_NAME} main.cpp)

# Add target dependencies
# This took me several hours because they've changed syntax used since 
# SFML v2.5 and there weren't many infomation about this :(
# Windows: Download SFML from website, extract the content and add 
#          path to /bin to Environment Variable (PATH) 
# MacOS  : Install brew, use brew to install cmake and sfml 
# Linux  : Use apt to install cmake and sfml 
find_package(SFML 2.5.1 COMPONENTS system graphics audio network REQUIRED)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)

# Add tests
include(CTest)
enable_testing()
include(CPack)
