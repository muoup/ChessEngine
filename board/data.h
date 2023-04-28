//
// Created by zbv11 on 27-Apr-23.
//

#ifndef CHESSENGINE_DATA_H
#define CHESSENGINE_DATA_H

#include <cstdint>

namespace posd {
    typedef uint8_t Square;
    typedef uint8_t Piece;

    const Piece EMPTY = 0;

    enum MoveType {
        NORMAL,
        CASTLE, EN_PASSANT,
        QPROM, RPROM, BPROM, NPROM
    };

    enum PieceType {
        NONE,
        PAWN,
        KNIGHT, BISHOP,
        ROOK,
        QUEEN, KING
    };

    struct Move {
        Square from;
        Square to;

        MoveType type;
    };

    struct EnPassantData {
        Square square;
        Piece piece;
    };

    Square square(uint8_t x, uint8_t y);
    Piece piece(PieceType type, bool white);

    bool sq_color(Square square);
    PieceType sq_type(Piece piece);
}

#endif //CHESSENGINE_DATA_H
