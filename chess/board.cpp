//
// Created by zbv11 on 26-Apr-23.
//

#include <iostream>
#include "board.h"

using namespace chess;

// FEN System:
// https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
Board::Board(std::string fen) : data(), squares() {
    int y = 7, x = 0;

    char* fen_ptr = &fen[0];
    while (*fen_ptr != ' ') {
        const auto c = *fen_ptr++;

        if (c == '/') {
            y--;
            x = 0;
        } else if (isdigit(c)) {
            x += c - '0';
        } else {
            squares[square(x, y)] = piece_fen(c);
            x++;
        }
    }

    bool turn = *(++fen_ptr) == 'w';

    // TODO: Castling Rights
    bool castlingRights[4] = { true, true, true, true };

    data.emplace(nullptr, *(new std::vector<Move>()), create_bits(turn, castlingRights), 0);
}

void Board::print() {
    for (int y = 7; y >= 0; y--) {
        for (int x = 0; x < 8; x++) {
            std::cout << to_char(squares[square(x, y)]);
        }
        std::cout << std::endl;
    }
}