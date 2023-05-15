#include <sstream>
#include "move.h"
#include "square.h"
#include "position.h"

using namespace chess;

void handle_rook_delta(const Square& rook_square, PositionData& data) {
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

void std_undo(Piece squares[], const PositionData& data) {
    const Move& move = data.prevMove;

    squares[move.from] = (move.promotion) ?
            squares[move.to] :
            Piece(PAWN, !piece_clr(move.promotion));
    squares[move.to] = EMPTY;
}

void std_play(const Move& move, Piece squares[], PositionData& data) {
    squares[move.to] = (move.promotion) ?
            squares[move.from] :
            move.promotion;
    squares[move.from] = EMPTY;

    if (piece_type(squares[move.from]) == KING)
        bitmask_castling_rights(data, turn(data) ? WHITE_CASTLE_MASK : BLACK_CASTLE_MASK, false);
    if (piece_type(squares[move.from]) == ROOK)
        handle_rook_delta(move.from, data);
}

std::string std_to_string(const Move& move) {
    std::stringstream ss;
    ss << (std::string) move.from << "-" << (std::string) move.to;
    if (move.promotion)
        ss << "=" << toupper((char) move.promotion);
    return ss.str();
}

void capture_undo(Piece squares[], const PositionData& data) {
    const Move& move = data.prevMove;

    squares[move.from] = (move.promotion) ?
            Piece(PAWN, !piece_clr(move.promotion)) :
            squares[move.to];
    squares[move.to] = move.captured_piece;
}

void capture_play(const Move& move, Piece squares[], PositionData& data) {
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

std::string capture_to_string(const Move& move) {
    std::stringstream ss;
    ss << (std::string) move.from << "x" << (std::string) move.to;
    if (move.promotion)
        ss << "=" << toupper((char) move.promotion);
    return ss.str();
}

void enpassant_undo(Piece squares[], const PositionData& data) {
    const Move &move = data.prevMove;

    squares[move.from] = squares[move.to];
    squares[move.to] = EMPTY;
    squares[move.enpassantSquare] =
            Piece(PAWN, !piece_clr(squares[move.from]));
}

void enpassant_play(const Move& move, Piece squares[], PositionData& data) {
    squares[move.to] = squares[move.from];
    squares[move.from] = EMPTY;
    squares[move.enpassantSquare] = EMPTY;
}

std::string enpassant_to_string(const Move& move) {
    std::stringstream ss;
    ss << (std::string) move.from << "x" << (std::string) move.to;
    return ss.str();
}

void castle_undo(Piece squares[], const PositionData& data) {
    const Move& move = data.prevMove;

    // This is duplicate code, but castle_play cannot be called as data is constant in this method.
    int8_t k_column = (move.from > move.to) ? 2 : 6;
    int8_t r_column = (move.from > move.to) ? 3 : 5;

    std::swap(squares[move.from],
              squares[Square(k_column, move.from.rank())]);

    std::swap(squares[move.to],
              squares[Square(r_column, move.to.rank())]);
}

void castle_play(const Move& move, Piece squares[], PositionData& data) {
    int8_t k_column = (move.from > move.to) ? 2 : 6;
    int8_t r_column = (move.from > move.to) ? 3 : 5;

    std::swap(squares[move.from],
              squares[Square(k_column, move.from.rank())]);

    std::swap(squares[move.to],
              squares[Square(r_column, move.to.rank())]);

    bitmask_castling_rights(data, turn(data) ? WHITE_CASTLE_MASK : BLACK_CASTLE_MASK, false);
}

std::string castle_to_string(const Move& move) {
    return (move.from > move.to) ? "O-O-O" : "O-O";
}

Move chess::std_move(const Piece squares[], const Square& from, const Square& to, PieceType promotion) {
    if (piece_type(squares[to]) != NONE)
        return capture_move(from, to, squares[to], promotion);

    return {
        .play = std_play,
        .undo = std_undo,
        .to_string = std_to_string,
        .from = from,
        .to = to,
        .promotion = Piece(promotion, piece_clr(squares[from]))
    };
}

Move chess::capture_move(const Square& from, const Square& to, const Piece& capture, PieceType promotion) {
    return {
        .play = capture_play,
        .undo = capture_undo,
        .to_string = capture_to_string,
        .from = from,
        .to = to,
        .enpassantSquare = NULL_SQUARE,
        .captured_piece = capture,
        .promotion = Piece(promotion, !piece_clr(capture))
    };
}

Move chess::enpassant_move(const Square& from, const Square& to, const Square& enpassantSquare) {
    return {
        .play = enpassant_play,
        .undo = enpassant_undo,
        .to_string = enpassant_to_string,
        .from = from,
        .to = to,
        .enpassantSquare = enpassantSquare,
    };
}

Move chess::castle_move(const Square& kingSquare, const Square& rookSquare) {
    return {
        .play = castle_play,
        .undo = castle_undo,
        .to_string = castle_to_string,
        .from = kingSquare,
        .to = rookSquare,
    };
}

std::string chess::to_string(const Move& move) {
    if (move.to_string == nullptr)
        throw std::runtime_error("Move has no to_string function");

    return move.to_string(move);
}