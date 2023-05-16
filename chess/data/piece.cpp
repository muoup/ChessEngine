#include <iostream>
#include <bitset>
#include "piece.h"

using namespace chess;

board_piece::board_piece(char c) {
    piece = CHAR_TO_TYPE.at(tolower(c)) << 1 | (isupper(c) ? 1 : 0);
}

board_piece::operator char() const {
    if (piece_type(piece) == NONE)
        return 'O';

    if (piece_type(piece) > KING) {
        std::cout << "\nInvalid piece type: " << std::bitset<8>(piece) << std::endl;
        exit(13);
    }

    char c = TYPE_TO_CHAR.at(piece_type(piece));
    return piece_clr(piece) ? (char) toupper(c) : c;
}

bool chess::piece_clr(const board_piece& piece) {
    return piece.piece & 1;
}

chess::PieceType chess::piece_type(const board_piece& piece) {
    return static_cast<PieceType>(piece.piece >> 1);
}

bool chess::is_enemy(const board_piece& piece, bool white) {
    return piece && piece_clr(piece) != white;
}

bool chess::is_ally(const board_piece& piece, bool white) {
    return piece && piece_clr(piece) == white;
}

board_piece::operator bool() const {
    return piece_type(piece) != NONE;
}