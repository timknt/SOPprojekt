cmake_minimum_required(VERSION 3.30)
project(SOPprojekt C)

set(CMAKE_C_STANDARD 23)

add_executable(Main main.c greppy_args.c linkedList.c readFile.c
        caseInsensitive.c)