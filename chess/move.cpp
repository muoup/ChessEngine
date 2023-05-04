#include "move.h"
#include "square.h"

using namespace chess;

void StdMove::UndoMove(Piece squares[], PositionData& data) {
    squares[from] = (promotion == 0) ?
            squares[to] :
            piece(PAWN, !piece_clr(promotion));
    squares[to] = EMPTY;
}

void StdMove::PlayMove(Piece squares[], PositionData& data) {
    squares[to] = (promotion == 0) ?
            squares[from] :
            piece((PieceType) promotion, !piece_clr(promotion));
    squares[from] = EMPTY;
}

void CaptureMove::UndoMove(Piece squares[], PositionData& data) {
    squares[from] = (promotion == 0) ?
            squares[to] :
            piece(PAWN, !piece_clr(promotion));
    squares[to] = captured;
}

void CaptureMove::PlayMove(Piece squares[], PositionData& data) {
    squares[to] = (promotion == 0) ?
            squares[from] :
            piece((PieceType) promotion, !piece_clr(promotion));
    squares[from] = EMPTY;
}

void EnPassantMove::UndoMove(Piece squares[], PositionData& data) {
    squares[from] = squares[to];
    squares[to] = EMPTY;
    squares[enpassantSquare] =
            piece(PAWN, !piece_clr(squares[from]));
}

void EnPassantMove::PlayMove(Piece squares[], PositionData& data) {
    squares[to] = squares[from];
    squares[from] = EMPTY;
    squares[enpassantSquare] = EMPTY;
}

void CastleMove::UndoMove(Piece squares[], PositionData& data) {
    PlayMove(squares, data);
}

void CastleMove::PlayMove(Piece squares[], PositionData& data) {
    int8_t k_column = (kingSquare > rookSquare) ? 2 : 6;
    int8_t r_column = (kingSquare > rookSquare) ? 3 : 5;

    std::swap(squares[kingSquare],
              squares[square(k_column, chess::rank(kingSquare))]);

    std::swap(squares[rookSquare],
              squares[square(r_column, chess::rank(rookSquare))]);
}

Move::~Move() {
    dyn_ptr_cmd(delete MOVE_PTR, NO_ARG);
}

void Move::PlayMove(Piece squares[], PositionData& data) {
    dyn_ptr_cmd(NO_ARG, MOVE_PTR->PlayMove(squares, data));


}

void Move::UndoMove(Piece squares[], PositionData& data) {
    dyn_ptr_cmd(NO_ARG, MOVE_PTR->UndoMove(squares, data));
}

Move&& chess::std_move(const Piece squares[], Square from, Square to, Piece promotion) {
    if (piece_type(squares[to]) != NONE)
        return capture_move(from, to, squares[to], promotion);

    void* move = new StdMove(from, to, promotion);

    return std::move(Move(move, NORMAL));
}

Move&& chess::capture_move(Square from, Square to, Piece capture, Piece promotion) {
    void* move = new CaptureMove(from, to, capture, promotion);

    return std::move(Move(move, CAPTURE));
}

Move&& chess::enpassant_move(Square from, Square to, Square enpassantSquare) {
    void* move = new EnPassantMove(from, to, enpassantSquare);

    return std::move(Move(move, ENPASSANT));
}

Move&& chess::castle_move(Square kingSquare, Square rookSquare) {
    void* move = new CastleMove(kingSquare, rookSquare);

    return std::move(Move(move, CASTLE));
}