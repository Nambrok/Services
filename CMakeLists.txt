cmake_minimum_required(VERSION 3.3.0)

project(Services C)

add_executable(services exo1.c)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
