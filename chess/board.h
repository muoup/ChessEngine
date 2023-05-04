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

        void PushMove(Move move);
        Move PopMove();

        void PlayMove(Move move);
        Move UndoMove();

        void print();

        Piece GetPieceAt(chess::Square square) {
            return squares[square];
        }
    private:
        std::stack<PositionData> data;
        Piece squares[64];
    };
}

#endif
