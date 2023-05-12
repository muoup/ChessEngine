#include <cctype>
#include "piece.h"

using namespace chess;

Piece::Piece(char c) {
    piece = (CHAR_TO_TYPE.at(tolower(c)) << 1) | (bool) isupper(c);
}

Piece::operator char() const {
    if (piece_type(piece) == NONE)
        return 'O';

    char c = TYPE_TO_CHAR.at(piece_type(piece));
    return piece_clr(piece) ? (char) toupper(c) : c;
}

bool chess::piece_clr(const Piece& piece) {
    return piece.piece & 1;
}

chess::PieceType chess::piece_type(const Piece& piece) {
    return static_cast<PieceType>(piece.piece >> 1);
}

bool chess::is_enemy(const Piece& piece, bool white) {
    return piece && piece_clr(piece) != white;
}

bool chess::is_ally(const Piece& piece, bool white) {
    return piece && piece_clr(piece) == white;
}