#include <cctype>
#include "piece.h"

chess::Piece chess::piece(PieceType type, bool white) {
    return (type << 1) | white;
}

chess::Piece chess::piece_fen(char c) {
    return (CHAR_TO_TYPE.at(tolower(c)) << 1) | (bool) isupper(c);
}

bool chess::piece_clr(Piece square) {
    return square & 1;
}

chess::PieceType chess::piece_type(Piece piece) {
    return static_cast<PieceType>(piece >> 1);
}

bool chess::is_empty(Piece piece) {
    return piece_type(piece) == EMPTY;
}

bool chess::is_enemy(Piece piece, bool white) {
    return !is_empty(piece) && piece_clr(piece) != white;
}

bool chess::is_ally(Piece piece, bool white) {
    return !is_empty(piece) && piece_clr(piece) == white;
}

char chess::to_char(Piece piece) {
    if (piece_type(piece) == NONE)
        return 'O';

    char c = TYPE_TO_CHAR.at(piece_type(piece));
    return piece_clr(piece) ? (char) toupper(c) : c;
}