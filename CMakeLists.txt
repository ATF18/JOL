cmake_minimum_required(VERSION 3.30)
project(PROJEKT)

set(CMAKE_CXX_STANDARD 17)

# SFML
set(SFML_DIR /opt/homebrew/Cellar/sfml@2/2.6.2/lib/cmake/SFML)
find_package(SFML 2.6.2 COMPONENTS system window graphics network audio REQUIRED)

# Gdzie szukać nagłówków (u Ciebie leżą w katalogu głównym projektu)
include_directories(${CMAKE_SOURCE_DIR})

# Dokładnie te pliki źródłowe skompiluj:
add_executable(PROJEKT
        main.cpp
        Gra.cpp
        Gracz.cpp
        Ziemia.cpp
        Platforma.cpp
)

target_link_libraries(PROJEKT
        sfml-system
        sfml-window
        sfml-graphics
        sfml-audio
        sfml-network
)
