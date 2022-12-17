cmake_minimum_required(VERSION 3.23)
project(Reversi)

set(CMAKE_CXX_STANDARD 14)

add_executable(Reversi
        src/Game.h
        src/Board.h
        src/Board.cpp
        src/Chips.h
        src/main.cpp src/Game.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

include_directories(C:/SFML/include)

target_link_libraries (Reversi sfml-graphics sfml-window sfml-audio sfml-system)