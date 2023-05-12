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
            SetSquare(x, y,c);
            x++;
        }
    }

    bool turn = *(++fen_ptr) == 'w';

    // TODO: Castling Rights
    bool castlingRights[4] = { true, true, true, true };

    data.push({
        .dataBits = create_bits(turn, castlingRights)
    });

    Print();
    PosEval();
}

void Board::Print() {
    for (int y = 7; y >= 0; y--) {
        for (int x = 0; x < 8; x++) {
            std::cout << (char) squares[Square(x, y)];
        }
        std::cout << std::endl;
    }
}

void Board::PlayMove(Move move) {
    PositionData pos = data.top();

    move.play(move, squares, pos);
    pos.prevMove = move;

    data.push(pos);
}

Move Board::UndoMove() {
    PositionData pos = data.top();

    Move move = pos.prevMove;
    move.undo(squares, pos);

    data.pop();

    return move;
}

void Board::SetSquare(Square square, Piece piece) {
    squares[square] = piece;
}

void Board::SetSquare(uint8_t x, uint8_t y, Piece piece) {
    squares[Square(x, y)] = piece;
}

Piece Board::GetSquare(Square square) {
    return squares[square];
}

void Board::PosEval() {
    pseudo_movegen(squares, data.top());

    PMPrint();
}

void Board::PMPrint() {
    std::cout << "Pseudo Legal Moves:" << std::endl;

    for (const Move& move : data.top().pseudoLegalMoves) {
        std::cout << to_string(move) << std::endl;
    }
}

const Piece *Board::GetSquares() {
    return squares;
}

Piece Board::PieceAt(chess::Square square) {
    return squares[square];
}
