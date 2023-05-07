#include "move.h"
#include "square.h"

using namespace chess;

void chess::std_undo(Move move, Piece squares[], PositionData& data) {
    squares[move.from] = (move.promotion == 0) ?
            squares[move.to] :
            piece(PAWN, !piece_clr(move.promotion));
    squares[move.to] = EMPTY;
}

void chess::std_play(Move move, Piece squares[], PositionData& data) {
    squares[move.to] = (move.promotion == 0) ?
            squares[move.from] :
            piece((PieceType) move.promotion, !piece_clr(move.promotion));
    squares[move.from] = EMPTY;
}

std::string chess::std_to_string(Move move) {
    return to_string(move.from) + "-" + to_string(move.to);
}

void chess::capture_undo(Move move, Piece squares[], PositionData& data) {
    squares[move.from] = (move.promotion == 0) ?
            squares[move.to] :
            piece(PAWN, !piece_clr(move.promotion));
    squares[move.to] = move.piece;
}

void chess::capture_play(Move move, Piece squares[], PositionData& data) {
    squares[move.to] = (move.promotion == 0) ?
            squares[move.from] :
            piece((PieceType) move.promotion, !piece_clr(move.promotion));
    squares[move.from] = EMPTY;
}

std::string chess::capture_to_string(Move move) {
    return to_string(move.from) + "x" + to_string(move.to);
}

void chess::enpassant_undo(Move move, Piece squares[], PositionData& data) {
    squares[move.from] = squares[move.to];
    squares[move.to] = EMPTY;
    squares[move.enpassantSquare] =
            piece(PAWN, !piece_clr(squares[move.from]));
}

void chess::enpassant_play(Move move, Piece squares[], PositionData& data) {
    squares[move.to] = squares[move.from];
    squares[move.from] = EMPTY;
    squares[move.enpassantSquare] = EMPTY;
}

std::string chess::enpassant_to_string(Move move) {
    return to_string(move.from) + "-" + to_string(move.to) + " e.p.";
}

void chess::castle_play(Move move, Piece squares[], PositionData& data) {
    int8_t k_column = (move.from > move.to) ? 2 : 6;
    int8_t r_column = (move.from > move.to) ? 3 : 5;

    std::swap(squares[move.from],
              squares[square(k_column, chess::rank(move.from))]);

    std::swap(squares[move.to],
              squares[square(r_column, chess::rank(move.to))]);
}

std::string chess::castle_to_string(Move move) {
    return (move.from > move.to) ? "O-O-O" : "O-O";
}

Move chess::std_move(const Piece squares[], Square from, Square to, Piece promotion) {
    if (piece_type(squares[to]) != NONE)
        return capture_move(from, to, squares[to], promotion);

    return {
        .play = std_play,
        .undo = std_undo,
        .to_string = std_to_string,
        .from =  from,
        .to =  to,
        .promotion =  promotion
    };
}

Move chess::capture_move(Square from, Square to, Piece capture, Piece promotion) {
    return {
        .play =  capture_play,
        .undo =  capture_undo,
        .to_string =  capture_to_string,
        .from =  from,
        .to =  to,
        .piece =  capture,
        .promotion =  promotion
    };
}

Move chess::enpassant_move(Square from, Square to, Square enpassantSquare) {
    return {
        .play =  enpassant_play,
        .undo =  enpassant_undo,
        .to_string =  enpassant_to_string,
        .from =  from,
        .to =  to,
        .enpassantSquare =  enpassantSquare
    };
}

Move chess::castle_move(Square kingSquare, Square rookSquare) {
    return {
        .play =  castle_play,
        .undo = castle_play,
        .to_string =  castle_to_string,
        .from =  kingSquare,
        .to =  rookSquare
    };
}

Move chess::empty_move() {
    return {
            nullptr,
            nullptr,
            nullptr,
            0, 0, 0, EMPTY, EMPTY
    };
}