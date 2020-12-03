# Initialize project
cmake_minimum_required(VERSION 3.0.0)
project(dungeon VERSION 0.1.0)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

# Set C++ standard, change this if you wish
set (CMAKE_CXX_STANDARD 17)

# Set target
add_executable(${PROJECT_NAME} main.cpp)
add_executable(text_ui TextUI.cpp)
# Add target dependencies
# Windows: Download SFML from website, extract the content and add 
#          path to /bin to Environment Variable (PATH) 
# MacOS  : Install brew, use brew to install cmake and sfml 
# Linux  : Use apt to install cmake and sfml 
find_package(SFML 2.5.1 COMPONENTS system graphics audio network REQUIRED)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio sfml-system sfml-window)

target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.1)

FetchContent_MakeAvailable(Catch2)


# Add tests
include(CTest)
enable_testing()

file(GLOB SOURCE_FILES CONFIGURE_DEPENDS
    "./*"
)
file(GLOB TEST_1 CONFIGURE_DEPENDS "./Grid.hpp" "./Grid.cpp")

set(TEST_DIR ../test)

add_library(dungeonlib STATIC ${TEST_1})
add_executable(mainTest ${TEST_DIR}/test.cpp)
target_link_libraries(mainTest
                        dungeonlib
                        Catch2::Catch2
                        sfml-graphics
                        sfml-audio
                        sfml-window
                        sfml-system    
)
add_test(mainTest mainTest)