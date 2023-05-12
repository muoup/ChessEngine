#ifndef CHESSENGINE_MOVE_H
#define CHESSENGINE_MOVE_H

#include <string>
#include <iostream>
#include <memory>
#include "square.h"
#include "piece.h"

namespace chess {
    struct PositionData;

    struct Move {
        void (*play)(const Move& move, Piece squares[], PositionData& data);
        void (*undo)(Piece squares[], const PositionData& data);
        std::string (*to_string)(const Move& move);

        // From and to also act as the king and rook squares for castling moves.
        Square from, to, enpassantSquare;
        Piece captured_piece, promotion;
    };

    std::string to_string(const Move& move);

    Move std_move(const Piece squares[], Square from, Square to, PieceType promotion = NONE);
    Move capture_move(Square from, Square to, Piece capture, PieceType promotion = NONE);
    Move castle_move(Square kingSquare, Square rookSquare);
    Move enpassant_move(Square from, Square to, Square enpassantSquare);
}

#endif