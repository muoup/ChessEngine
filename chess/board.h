#ifndef CHESSENGINE_BOARD_H
#define CHESSENGINE_BOARD_H

#include <stack>
#include <memory>
#include <vector>
#include "position.h"

namespace chess {
    class Board {
    public:
        explicit Board(std::string fen);
        Board() : Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1") {}

        void play_move(const Move& move);
        Move undo_move();

        void set_square(Square square, const Piece& piece);
        void set_square(uint8_t x, uint8_t y, const Piece& piece);

        void print();

        const Piece *get_squares();
        Piece piece_at(chess::Square square);

        operator Piece*();

        void pm_print();
    private:
        std::stack<PositionData> data;
        Piece squares[64];

        void pos_eval();
    };
}

#endif
