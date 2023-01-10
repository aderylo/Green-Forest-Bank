cmake_minimum_required(VERSION 3.0.0)
project(zad3 VERSION 0.1.0)

add_executable(zad3 src/main.c src/utils/vector.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})