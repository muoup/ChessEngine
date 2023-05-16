#include "moveengine.h"
#include <vector>

#define moveadd() position.add_move(std_move(squares, square, to))
#define moveaddp(promotion) position.add_move(std_move(squares, square, to, promotion))

#define offset_move(dx, dy) \
    if ((to = shift(square, dx, dy)).valid() && !is_ally(squares[to], wturn)) \
        moveadd()
#define dir_move(dx, dy) \
    for (int8_t xx = dx, yy = dy; (to = shift(square, xx, yy)).valid() && !is_ally(squares[to], wturn); xx += dx, yy += dy) { \
        moveadd(); \
        if (squares[to]) break; \
    }

using namespace chess;

void pawn_gen(const Piece squares[], PositionData& position, const Square& square) {
    bool wturn = turn(position);
    int8_t dir = wturn ? 1 : -1;
    Square to;

    if (!squares[to = shift(square, 0, dir)]) {
        if (square.rank() == (wturn ? 6 : 1)) {
            moveaddp(QUEEN);
            moveaddp(ROOK);
            moveaddp(BISHOP);
            moveaddp(KNIGHT);
        } else {
            moveadd();
            if (!squares[to = shift(to, 0, dir)])
                position.add_move(std_move(squares, square, to, NONE, shift(square, 0, dir)));
        }
    }

    if (square.rank() > 0 && is_enemy(squares[to = shift(square, 1, dir)], wturn))
        moveadd();
    if (position.en_passant && (position.en_passant == to))
        position.add_move(en_passant_move(square, to, shift(to, 0, dir)));
    if (square.rank() < 7 && is_enemy(squares[to = shift(square, -1, dir)], wturn))
        moveadd();
    if (position.en_passant && (position.en_passant == to))
        position.add_move(en_passant_move(square, to, shift(to, 0, dir)));
}

void knight_gen(const Piece squares[], PositionData& position, const Square& square) {
    bool wturn = turn(position);
    Square to;

    offset_move(1, 2);
    offset_move(2, 1);
    offset_move(2, -1);
    offset_move(1, -2);
    offset_move(-1, -2);
    offset_move(-2, -1);
    offset_move(-2, 1);
    offset_move(-1, 2);
}

void bishop_gen(const Piece squares[], PositionData& position, const Square& square) {
    bool wturn = turn(position);
    Square to;

    dir_move(1, 1);
    dir_move(1, -1);
    dir_move(-1, -1);
    dir_move(-1, 1);
}

void rook_gen(const Piece squares[], PositionData& position, const Square& square) {
    bool wturn = turn(position);
    Square to;

    dir_move(1, 0);
    dir_move(0, 1);
    dir_move(-1, 0);
    dir_move(0, -1);
}

void king_gen(const Piece squares[], PositionData& position, const Square& square) {
    bool wturn = turn(position);
    Square to;

    for (int8_t dx = -1; dx <= 1; dx++)
        for (int8_t dy = -1; dy <= 1; dy++)
            offset_move(dx, dy);

    if (has_castling_rights(position, (CastlingType) (2 * wturn))) {
        // King-side castling
        if (!squares[shift(square, 1, 0)]
         && !squares[to = shift(square, 2, 0)]) {

            position.add_move(castle_move(square, to));
        }
    }
    if (has_castling_rights(position, (CastlingType) (2 * wturn + 1))) {
        // Queen-side castling
        if (!squares[shift(square, -1, 0)]
         && !squares[shift(square, -2, 0)]
         && !squares[to = shift(square, -3, 0)]) {

            position.add_move(castle_move(square, to));
        }
    }
}

void chess::pseudo_movegen(const Piece squares[], PositionData& position) {
    for (uint8_t i = 0; i < 64; i++) {
        if (!squares[i]
         || piece_clr(squares[i]) != turn(position)) continue;

        switch (piece_type(squares[i])) {
            case PAWN:
                pawn_gen(squares, position, i);
                break;
#if 0
            case KNIGHT:
                knight_gen(squares, position, i);
                break;
            case BISHOP:
                bishop_gen(squares, position, i);
                break;
            case ROOK:
                rook_gen(squares, position, i);
                break;
            case QUEEN:
                bishop_gen(squares, position, i);
                rook_gen(squares, position, i);
                break;
            case KING:
                king_gen(squares, position, i);
                break;
            default:
                break;
#endif
        }
    }
}