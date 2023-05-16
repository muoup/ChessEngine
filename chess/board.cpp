#include <iostream>
#include "board.h"
#include "parsing/pseudomovegen.h"

using namespace chess;

// FEN System:
// https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
board::board(std::string fen) : data(), squares() {
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
    bool castling_rights[4] = {false, false, false, false };

    fen_ptr++;

    while (*(++fen_ptr) != ' ') {
        switch (*fen_ptr) {
            case 'K':
                castling_rights[WHITE_KING_SIDE] = true;
                break;
            case 'Q':
                castling_rights[WHITE_QUEEN_SIDE] = true;
                break;
            case 'k':
                castling_rights[BLACK_KING_SIDE] = true;
                break;
            case 'q':
                castling_rights[BLACK_QUEEN_SIDE] = true;
                break;
            default:
                std::cout << "Invalid castling rights: " << *fen_ptr << std::endl;
                // TODO: Throw exception
                break;
        }
    }

    data.push({
        .dataBits = create_bits(turn, castling_rights),
    });

    pos_eval();
}

void board::print() {
    std::cout << " BOARD:\n";
    for (int y = 7; y >= 0; y--) {
        for (int x = 0; x < 8; x++) {
            std::cout << (char) squares[board_square(x, y)];
        }
        std::cout << "\n";
    }
}

void board::play_move(const board_move& move) {
    position_data pos = data.top();

    pos.en_passant = 0;
    pos.prev_move = move;
    pos.pseudo_legal_moves.clear();

    move.method_refs->play(move, squares, pos);

    data.push(pos);

    pos_eval();
}

board_move board::undo_move() {
    position_data pos = data.top();

    board_move move = pos.prev_move;
    move.method_refs->undo(squares, pos);

    data.pop();

    return move;
}

void board::set_square(board_square square, const board_piece& piece) {
    squares[square] = piece;
}

void board::set_square(uint8_t x, uint8_t y, const board_piece& piece) {
    squares[board_square(x, y)] = piece;
}

void board::pos_eval() {
    movegen::pseudo_movegen(squares, data.top());
}

void board::pm_print() {
    std::cout << "Pseudo Legal Moves:" << std::endl;

    auto& moves = data.top().pseudo_legal_moves;

    for (const board_move& move : moves) {
        std::cout << to_string(move) << std::endl;
    }
}

const board_piece *board::get_squares() {
    return squares;
}

board_piece board::piece_at(chess::board_square square) {
    return squares[square];
}

board::operator board_piece*() {
    return squares;
}
