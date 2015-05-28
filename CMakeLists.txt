
cmake_minimum_required(VERSION 3.0.2)

project(curses-test)

list(APPEND ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(Curses REQUIRED)

set(curses-test_MAJOR_VERSION 0)
set(curses-test_MINOR_VERSION 0)
set(curses-test_PATCH_VERSION 1)
set(curses-test_VERSION ${curses-test_MAJOR_VERSION}.${curses-test_MINOR_VERSION}.${curses-test_PATCH_VERSION})

add_definitions(-std=c11)

include_directories(. include ${CMAKE_BINARY_DIR} ${CURSES_INCLUDE_DIRS})

#TODO: use add_subdirectory instead, and add test directory
add_executable(curses-test src/main.c)

target_link_libraries(curses-test ${CURSES_LIBRARIES})

