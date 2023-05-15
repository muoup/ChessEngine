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

    Move std_move(const Piece squares[], const Square& from, const Square& to, PieceType promotion = NONE);
    Move capture_move(const Square& from, const Square& to, const Piece& capture, PieceType promotion = NONE);
    Move castle_move(const Square& kingSquare, const Square& rookSquare);
    Move enpassant_move(const Square& from, const Square& to, const Square& enpassantSquare);
}

#endif