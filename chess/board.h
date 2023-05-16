#ifndef CHESSENGINE_BOARD_H
#define CHESSENGINE_BOARD_H

#include <stack>
#include <memory>
#include <vector>
#include "data/position.h"

namespace chess {
    class board {
    public:
        explicit board(std::string fen);
        board() : board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1") {}

        void play_move(const board_move& move);
        board_move undo_move();

        void set_square(board_square square, const board_piece& piece);
        void set_square(uint8_t x, uint8_t y, const board_piece& piece);

        void print();

        const board_piece *get_squares();
        board_piece piece_at(chess::board_square square);

        operator board_piece*();

        void pm_print();
    private:
        std::stack<position_data> data;
        board_piece squares[64];

        void pos_eval();
    };
}

#endif
