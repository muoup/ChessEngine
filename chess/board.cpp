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

    // This can be optimized a bit with a std::bitset and/or an inline use of the logic of create_bits,
    // however since this is only called once per game, it's not worth the effort
    bool turn = *(++fen_ptr) == 'w';
    bool castlingRights[4] = { false, false, false, false };

    fen_ptr++;

    while (*(++fen_ptr) != ' ') {
        switch (*fen_ptr) {
            case 'K':
                castlingRights[0] = true;
                break;
            case 'Q':
                castlingRights[1] = true;
                break;
            case 'k':
                castlingRights[2] = true;
                break;
            case 'q':
                castlingRights[3] = true;
                break;
            default:
                std::cout << "Invalid castling rights: " << *fen_ptr << std::endl;
                // TODO: Throw exception
                break;
        }
    }

    data.push({
        .dataBits = create_bits(turn, castlingRights)
    });

    Print();
    PosEval();
}

void Board::Print() {
    std::cout << " BOARD:\n";
    for (int y = 7; y >= 0; y--) {
        for (int x = 0; x < 8; x++) {
            std::cout << (char) squares[Square(x, y)];
        }
        std::cout << "\n";
    }
}

void Board::PlayMove(const Move& move) {
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

void Board::SetSquare(Square square, const Piece& piece) {
    squares[square] = piece;
}

void Board::SetSquare(uint8_t x, uint8_t y, const Piece& piece) {
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

    auto& moves = data.top().pseudoLegalMoves;

    for (const Move& move : moves) {
        std::cout << to_string(move) << std::endl;
    }
}

const Piece *Board::GetSquares() {
    return squares;
}

Piece Board::PieceAt(chess::Square square) {
    return squares[square];
}
