cmake_minimum_required(VERSION 3.0.0)
project(zad3 VERSION 0.1.0)

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE "Release")
endif ()

set(CMAKE_C_FLAGS "-std=c17 -Wall -Wextra -Wno-implicit-fallthrough")
set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG")
set(CMAKE_C_FLAGS_DEBUG "-g")

add_executable(zad3 src/main.c src/utils/vector.c)
add_executable(fts src/fts.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})