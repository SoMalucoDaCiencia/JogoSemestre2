cmake_minimum_required(VERSION 3.23)
project(JogoSemestre2 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(deps)
include_directories($ENV{ALLEGRO}/include) # Definir pasta do alegro como uma variavel de ambiente com nome "ALLEGRO"
link_directories($ENV{ALLEGRO}/lib)

add_executable(JogoSemestre2
        deps/nossaLivraria.c
        deps/nossaLivraria.h
        src/main.c)

if (WIN32)
    target_link_libraries(JogoSemestre2 -lmingw32 -lallegro-5.0.10-monolith-md-debug)
elseif (APPLE)
    file(GLOB MyCSources $ENV{ALLEGRO}/lib/*.dylib)
    target_link_libraries(JogoSemestre2 ${MyCSources})
endif()
