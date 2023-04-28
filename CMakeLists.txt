cmake_minimum_required(VERSION 3.16)
project(ChessEngine)

set(CMAKE_CXX_STANDARD 17)

add_executable(ChessEngine main.cpp board/board.cpp board/board.h board/position.cpp board/position.h board/move.cpp board/move.h board/data.cpp board/data.h)
