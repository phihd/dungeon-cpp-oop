# Initialize project
cmake_minimum_required(VERSION 3.0.0)
project(dungeon VERSION 0.1.0)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

# Add SFML library
find_package(SFML 2.5.1 COMPONENTS system graphics audio network REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

# Set target
add_executable(dungeon main.cpp)

# Add target dependencies
target_link_libraries(dungeon ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

# Add tests
include(CTest)
enable_testing()
include(CPack)
