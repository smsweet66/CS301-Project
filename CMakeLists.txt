cmake_minimum_required(VERSION 3.16)
project(CS301_Project C)

set(CMAKE_C_STANDARD 99)

add_executable(CS301_Project main.c sort.c database.c)
FILE(REMOVE ${PROJECT_BINARY_DIR}/data.txt ${PROJECT_BINARY_DIR}/input.txt)
FILE(COPY data.txt input.txt DESTINATION ${PROJECT_BINARY_DIR})