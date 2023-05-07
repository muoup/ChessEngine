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
        void (*play)(Move move, Piece squares[], PositionData& data);
        void (*undo)(Move move, Piece squares[], PositionData& data);
        std::string (*to_string)(Move move);

        // From and to also act as the king and rook squares for castling moves.
        Square from, to, enpassantSquare;
        Piece piece, promotion;
    };

    void std_play(Move move, Piece squares[], PositionData& data);
    void std_undo(Move move, Piece squares[], PositionData& data);
    std::string std_to_string(Move move);

    void capture_play(Move move, Piece squares[], PositionData& data);
    void capture_undo(Move move, Piece squares[], PositionData& data);
    std::string capture_to_string(Move move);

    void castle_play(Move move, Piece squares[], PositionData& data);
    std::string castle_to_string(Move move);

    void enpassant_play(Move move, Piece squares[], PositionData& data);
    void enpassant_undo(Move move, Piece squares[], PositionData& data);
    std::string enpassant_to_string(Move move);

    Move std_move(const Piece squares[], Square from, Square to, Piece promotion = EMPTY);
    Move capture_move(Square from, Square to, Piece captured, Piece promotion = EMPTY);
    Move castle_move(Square kingSquare, Square rookSquare);
    Move enpassant_move(Square from, Square to, Square enpassantSquare);
}

#endif