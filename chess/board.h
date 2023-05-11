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

        void PlayMove(Move move);
        Move UndoMove();

        void Print();

        const Piece *GetSquares() {
            return squares;
        }

        Piece PieceAt(chess::Square square) {
            return squares[square];
        }
    private:
        std::stack<PositionData> data;
        Piece squares[64];

        void PosEval();
        void PMPrint();
    };
}

#endif
