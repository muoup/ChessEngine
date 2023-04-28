//
// Created by zbv11 on 27-Apr-23.
//

#include "data.h"

posd::Square posd::square(uint8_t x, uint8_t y) {
    return (x << 4) | y;
}

posd::Piece posd::piece(PieceType type, bool white) {
    return (type << 1) | white;
}

bool posd::sq_color(Square square) {
    return square & 1;
}

posd::PieceType posd::sq_type(Piece piece) {
    return static_cast<PieceType>(piece >> 1);
}