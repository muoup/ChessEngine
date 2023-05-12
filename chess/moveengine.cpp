#include "moveengine.h"
#include <vector>

#define moveadd() position.AddMove(std_move(squares, square, to))
#define moveaddp(promotion) position.AddMove(std_move(squares, square, to, promotion))

#define knight_move(dx, dy) if ((to = shift(square, dx, dy)) && !is_ally(squares[to], wturn)) moveadd()

using namespace chess;

void pawn_gen(const Piece squares[], PositionData& position, Square square) {
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
                moveadd();
        }
    }

    if (square.rank() > 0 && is_enemy(squares[to = shift(square, 1, dir)], wturn))
        moveadd();
    if (square.rank() < 7 && is_enemy(squares[to = shift(square, -1, dir)], wturn))
        moveadd();

    // TODO: En passant
}

void knight_gen(const Piece squares[], PositionData& position, Square square) {
    bool wturn = turn(position);
    Square to;

    knight_move(1, 2);
    knight_move(2, 1);
    knight_move(2, -1);
    knight_move(1, -2);
    knight_move(-1, -2);
    knight_move(-2, -1);
    knight_move(-2, 1);
    knight_move(-1, 2);
}

void chess::pseudo_movegen(const Piece squares[], PositionData& position) {
    for (uint8_t i = 0; i < 64; i++) {
        if (!squares[i]
         || piece_clr(squares[i]) != turn(position)) continue;

        switch (piece_type(squares[i])) {
            case PAWN:
                pawn_gen(squares, position, i);
                break;
            case KNIGHT:
                knight_gen(squares, position, i);
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