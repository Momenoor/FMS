cmake_minimum_required(VERSION 3.27)
project(FMS)

# Assuming the project is in C, not C++
set(CMAKE_C_STANDARD 99)

# Listing the C files for compilation
add_executable(FMS
        client.c
        index.c
        reservation.c
        main.c
        client.h
        reservation.h
        index.h
        struct.h
        main.c)
