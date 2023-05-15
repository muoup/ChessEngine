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

        void PlayMove(const Move& move);
        Move UndoMove();

        void SetSquare(Square square, const Piece& piece);
        void SetSquare(uint8_t x, uint8_t y, const Piece& piece);
        Piece GetSquare(Square square);

        void Print();

        const Piece *GetSquares();
        Piece PieceAt(chess::Square square);
    private:
        std::stack<PositionData> data;
        Piece squares[64];

        void PosEval();
        void PMPrint();
    };
}

#endif
