cmake_minimum_required(VERSION 3.23)
project(JogoSemestre2 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(deps)
include_directories($ENV{ALLEGRO})

add_executable(JogoSemestre2
        deps/nossaLivraria.c
        deps/nossaLivraria.h
        src/main.c)

target_link_libraries(JogoSemestre2 -lmingw32 -lallegro-5.0.10-monolith-md-debug)
