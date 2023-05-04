cmake_minimum_required(VERSION 3.20)
project(ChessEngine)

set(CMAKE_CXX_STANDARD 20)

add_executable(ChessEngine main.cpp chess/board.cpp chess/board.h chess/position.cpp chess/position.h chess/move.cpp chess/move.h chess/square.cpp chess/square.h chess/piece.cpp chess/piece.h chess/MoveEngine.cpp chess/MoveEngine.h util/vector_view.cpp util/vector_view.h)
