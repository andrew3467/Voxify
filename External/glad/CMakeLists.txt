cmake_minimum_required(VERSION 3.27)
project(glad)

set(CMAKE_CXX_STANDARD 23)

set(SOURCE
    src/gl.c
)

set(HEADERS
    include/glad/gl.h
        include/KHR/khrplatform.h
)

include_directories(./include)

add_library(glad
        ${SOURCE}
        ${HEADERS}
)