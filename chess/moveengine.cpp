#include "moveengine.h"
#include <vector>

using namespace chess;

void pawn_gen(const Piece squares[], const chess::PositionData& position, Square square) {
    bool wturn = turn(position);
    int8_t dir = wturn ? 1 : -1;
    Square to;

    std::vector<Move>& moves = position.pseudoLegalMoves;

    if (is_empty(squares[to = shift(square, 0, dir)])) {
        if (rank(square) == (wturn ? 1 : 6)) {
            moves.push_back(std_move(squares, square, to, QUEEN));
            moves.push_back(std_move(squares, square, to, ROOK));
            moves.push_back(std_move(squares, square, to, BISHOP));
            moves.push_back(std_move(squares, square, to, KNIGHT));
        } else {
            moves.push_back(std_move(squares, square, to));
            if (is_empty(squares[to = shift(to, 0, dir)]))
                moves.push_back(std_move(squares, square, to));
        }
    }

    if (is_enemy(squares[to = shift(square, 1, dir)], wturn))
        moves.push_back(std_move(squares, square, to));
    if (is_enemy(squares[to = shift(square, -1, dir)], wturn))
        moves.push_back(std_move(squares, square, to));

    // TODO: En passant
}

void knight_gen(const Piece squares[], const chess::PositionData& data, Square square) {

}

void pseudo_movegen(const Piece squares[], const chess::PositionData& data) {
    for (uint8_t i = 0; i < 64; i++) {
        if (piece_type(squares[i]) == EMPTY
         || piece_clr(squares[i]) != turn(data)) continue;

        switch (piece_type(squares[i])) {
            case PAWN:
                pawn_gen(squares, data, i);
                break;
            case KNIGHT:
                break;
            case BISHOP:
                break;
            case ROOK:
                break;
            case QUEEN:
                break;
            case KING:
                break;
            default:
                break;
        }
    }
}