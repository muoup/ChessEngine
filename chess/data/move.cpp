#include <sstream>
#include "move.h"
#include "square.h"
#include "position.h"

#define castle_swap() \
    const int8_t k_column = (move.from > move.to) ? 2 : 6; \
    const int8_t r_column = (move.from > move.to) ? 3 : 5; \
    std::swap(squares[move.from], squares[board_square(k_column, move.from.rank())]); \
    std::swap(squares[move.to], squares[board_square(r_column, move.to.rank())])

using namespace chess;

void handle_rook_delta(const board_square& rook_square, position_data& data) {
    switch (rook_square) {
        case W_K_ROOK:
            set_castling_rights(data, WHITE_KING_SIDE, false);
            break;
        case W_Q_ROOK:
            set_castling_rights(data, WHITE_QUEEN_SIDE, false);
            break;
        case B_K_ROOK:
            set_castling_rights(data, BLACK_KING_SIDE, false);
            break;
        case B_Q_ROOK:
            set_castling_rights(data, BLACK_QUEEN_SIDE, false);
            break;
    }
}

void move_functions::std_undo(board_piece squares[], const position_data& data) {
    const board_move& move = data.prev_move;

    squares[move.from] = (move.promotion) ?
                         board_piece(PAWN, !piece_clr(move.promotion)) :
                         squares[move.to];
    squares[move.to] = EMPTY;
}

void move_functions::std_play(const board_move& move, board_piece squares[], position_data& data) {
    squares[move.to] = (move.promotion) ?
            move.promotion :
            squares[move.from];
    squares[move.from] = EMPTY;

    data.en_passant = move.en_passant;

    if (piece_type(squares[move.from]) == KING)
        bitmask_castling_rights(data, turn(data) ? WHITE_CASTLE_MASK : BLACK_CASTLE_MASK, false);
    if (piece_type(squares[move.from]) == ROOK)
        handle_rook_delta(move.from, data);
}

std::string move_functions::std_to_string(const board_move& move) {
    std::stringstream ss;
    ss << (std::string) move.from << "-" << (std::string) move.to;
    if (move.promotion)
        ss << "=" << toupper((char) move.promotion);
    return ss.str();
}

void move_functions::capture_undo(board_piece squares[], const position_data& data) {
    const board_move& move = data.prev_move;

    squares[move.from] = (move.promotion) ?
                         board_piece(PAWN, !piece_clr(move.promotion)) :
                         squares[move.to];
    squares[move.to] = move.captured_piece;
}

void move_functions::capture_play(const board_move& move, board_piece squares[], position_data& data) {
    squares[move.to] = (move.promotion) ?
            move.promotion :
           squares[move.from];
    squares[move.from] = EMPTY;

    if (piece_type(squares[move.from]) == KING)
        bitmask_castling_rights(data, turn(data) ? WHITE_CASTLE_MASK : BLACK_CASTLE_MASK, false);
    if (piece_type(squares[move.from]) == ROOK)
        handle_rook_delta(move.from, data);
    if (piece_type(squares[move.to]) == ROOK)
        handle_rook_delta(move.to, data);
}

std::string move_functions::capture_to_string(const board_move& move) {
    std::stringstream ss;
    ss << (std::string) move.from << "x" << (std::string) move.to;
    if (move.promotion)
        ss << "=" << toupper((char) move.promotion);
    return ss.str();
}

void move_functions::en_passant_undo(board_piece squares[], const position_data& data) {
    const board_move &move = data.prev_move;

    squares[move.from] = squares[move.to];
    squares[move.to] = EMPTY;
    squares[move.en_passant] =
            board_piece(PAWN, !piece_clr(squares[move.from]));
}

void move_functions::en_passant_play(const board_move& move, board_piece squares[], position_data& data) {
    squares[move.to] = squares[move.from];
    squares[move.from] = EMPTY;
    squares[move.en_passant] = EMPTY;
}

std::string move_functions::en_passant_to_string(const board_move& move) {
    std::stringstream ss;
    ss << (std::string) move.from << "x" << (std::string) move.to << " (e.p.)";
    return ss.str();
}

void move_functions::castle_undo(board_piece squares[], const position_data& data) {
    const board_move& move = data.prev_move;

    castle_swap();
}

void move_functions::castle_play(const board_move& move, board_piece squares[], position_data& data) {
    castle_swap();

    bitmask_castling_rights(data, turn(data) ? WHITE_CASTLE_MASK : BLACK_CASTLE_MASK, false);
}

std::string move_functions::castle_to_string(const board_move& move) {
    return (move.from > move.to) ? "O-O-O" : "O-O";
}

board_move chess::std_move(const board_piece squares[], const board_square& from, const board_square& to, PieceType promotion) {
    if (piece_type(squares[to]) != NONE)
        return capture_move(from, to, squares[to], promotion);

    return {
        .method_refs = &move_data[STANDARD],
        .from = from,
        .to = to,
        .promotion = board_piece(promotion, piece_clr(squares[from]))
    };
}

board_move chess::ptwo_move(const board_square& from, const board_square& to) {
    auto diff = from < to ? -1 : 1;

    return {
            .method_refs = &move_data[STANDARD],
            .from = from,
            .to = to,
            .en_passant = shift(to, 0, diff),
    };
}

board_move chess::capture_move(const board_square& from, const board_square& to, const board_piece& capture, PieceType promotion) {
    return {
        .method_refs = &move_data[CAPTURE],
        .from = from,
        .to = to,
        .captured_piece = capture,
        .promotion = board_piece(promotion, !piece_clr(capture))
    };
}

board_move chess::en_passant_move(const board_square& from, const board_square& to, const board_square& en_passant_square) {
    return {
        .method_refs = &move_data[EN_PASSANT],
        .from = from,
        .to = to,
        .en_passant = en_passant_square,
    };
}

board_move chess::castle_move(const board_square& king_square, const board_square& rook_square) {
    return {
        .method_refs = &move_data[CASTLE],
        .from = king_square,
        .to = rook_square,
    };
}

std::string chess::to_string(const board_move& move) {
    if (move.method_refs->to_string == nullptr)
        throw std::runtime_error("Move has no to_string function");

    return move.method_refs->to_string(move);
}