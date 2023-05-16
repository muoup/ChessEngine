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
            set_square(x, y, c);
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
                castlingRights[WHITE_KING_SIDE] = true;
                break;
            case 'Q':
                castlingRights[WHITE_QUEEN_SIDE] = true;
                break;
            case 'k':
                castlingRights[BLACK_KING_SIDE] = true;
                break;
            case 'q':
                castlingRights[BLACK_QUEEN_SIDE] = true;
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

    pos_eval();
}

void Board::print() {
    std::cout << " BOARD:\n";
    for (int y = 7; y >= 0; y--) {
        for (int x = 0; x < 8; x++) {
            std::cout << (char) squares[Square(x, y)];
        }
        std::cout << "\n";
    }
}

void Board::play_move(const Move& move) {
    PositionData pos = data.top();

    pos.en_passant = 0;
    pos.prev_move = move;
    pos.pseudo_legal_moves.clear();

    move.play(move, squares, pos);

    data.push(pos);

    pos_eval();
}

Move Board::undo_move() {
    PositionData pos = data.top();

    Move move = pos.prev_move;
    move.undo(squares, pos);

    data.pop();

    return move;
}

void Board::set_square(Square square, const Piece& piece) {
    squares[square] = piece;
}

void Board::set_square(uint8_t x, uint8_t y, const Piece& piece) {
    squares[Square(x, y)] = piece;
}

void Board::pos_eval() {
    pseudo_movegen(squares, data.top());
}

void Board::pm_print() {
    std::cout << "Pseudo Legal Moves:" << std::endl;

    auto& moves = data.top().pseudo_legal_moves;

    for (const Move& move : moves) {
        std::cout << to_string(move) << std::endl;
    }
}

const Piece *Board::get_squares() {
    return squares;
}

Piece Board::piece_at(chess::Square square) {
    return squares[square];
}

Board::operator Piece*() {
    return squares;
}
