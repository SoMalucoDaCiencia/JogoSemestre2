cmake_minimum_required(VERSION 3.23)
project(JogoSemestre2 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(deps)

add_executable(JogoSemestre2
        deps/nossaLivraria.c
        deps/nossaLivraria.h
        src/main.c)
