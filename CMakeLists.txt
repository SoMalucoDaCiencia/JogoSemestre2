cmake_minimum_required(VERSION 3.23)
project(JogoSemestre2)
EXECUTE_PROCESS( COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE )
message( STATUS "Architecture: ${ARCHITECTURE}")

set(CMAKE_CXX_STANDARD 11)

include_directories(.)
include_directories(innerIncludes)
include_directories($ENV{ALLEGRO}/include) # Definir pasta do alegro como uma variavel de ambiente com nome "ALLEGRO"
link_directories($ENV{ALLEGRO}/lib)

add_executable(JogoSemestre2
        innerIncludes/headers/Cores.h
        innerIncludes/Cores.c
        innerIncludes/headers/yamlReader.h
        innerIncludes/yamlReader.c
        innerIncludes/headers/nossaLivraria.h
        innerIncludes/nossaLivraria.c
        innerIncludes/headers/gameCore.h
        innerIncludes/gameCore.c
        outIncludes/algif.c
        outIncludes/headers/algif.h
        outIncludes/gif.c
        outIncludes/bitmap.c
        outIncludes/lzw.c
        src/main.h
        src/main.c)

if (WIN32)
    target_link_libraries(JogoSemestre2 -lmingw32 -lallegro-5.0.10-monolith-md-debug)
elseif (APPLE)
    if (${ARCHITECTURE} STREQUAL "arm64")
        set(CMAKE_OSX_ARCHITECTURES "x86_64" CACHE INTERNAL "" FORCE)
    endif()
    file(GLOB MyCSources $ENV{ALLEGRO}/lib/*.dylib)
    target_link_libraries(JogoSemestre2 ${MyCSources})
endif()
