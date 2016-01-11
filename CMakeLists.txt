cmake_minimum_required(VERSION 3.3)
project(21sh)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        includes
        libft
        srcs
        srcs/main.c
        )
add_executable(21sh ${SOURCE_FILES})