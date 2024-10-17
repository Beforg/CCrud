cmake_minimum_required(VERSION 3.29)
project(CCrud C)

set(CMAKE_C_STANDARD 11)

add_executable(CCrud main.c
        service.h
        service.c
        nav.c
        nav.h
)
