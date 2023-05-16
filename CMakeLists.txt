cmake_minimum_required(VERSION 3.20)
project(ChessEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(ChessEngine main.cpp chess/board.cpp chess/board.h chess/data/position.cpp chess/data/position.h chess/data/move.cpp chess/data/move.h chess/data/square.cpp chess/data/square.h chess/data/piece.cpp chess/data/piece.h chess/parsing/pseudomovegen.cpp chess/parsing/pseudomovegen.h chess/parsing/legalcheck.cpp chess/parsing/legalcheck.h)
