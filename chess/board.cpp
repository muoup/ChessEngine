#include <iostream>
#include "board.h"
#include "moveengine.h"

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

    data.emplace(chess::empty_move(), *(new std::vector<Move>()), create_bits(turn, castlingRights), 0);

    PosEval();
}

void Board::Print() {
    for (int y = 7; y >= 0; y--) {
        for (int x = 0; x < 8; x++) {
            std::cout << to_char(squares[square(x, y)]);
        }
        std::cout << std::endl;
    }
}

void Board::PlayMove(Move move) {
    PositionData pos = data.top();

    move.play(move, squares, pos);
    pos.pseudoLegalMoves = *(new std::vector<Move>());
    pos.prevMove = move;

    data.push(pos);
}

// Q: If you std::move a class, will its destructor be called?
// A: Yes, it will be called.
// https://stackoverflow.com/questions/3106110/does-stdmove-call-the-move-constructor

Move Board::UndoMove() {
    PositionData pos = data.top();
    Move move = pos.prevMove;
    move.undo(squares, pos);

    pos.handle_deconstruct();
    data.pop();

    return move;
}

void Board::PosEval() {
    pseudo_movegen(squares, data.top());

    PMPrint();
}

void Board::PMPrint() {
    std::cout << "Pseudo Legal Moves:" << std::endl;
    for (Move move : data.top().pseudoLegalMoves) {
        std::cout << to_string(move) << std::endl;
    }
}
