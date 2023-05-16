#include "legalcheck.h"

using namespace chess;

struct raycast_data {
    uint8_t dist;
    board_piece piece;
};

raycast_data raycast(const board_piece squares[], board_square square, uint8_t dx, uint8_t dy) {
    board_square current = square;
    for (uint8_t i = 0; current.valid(); i++) {
        current = shift(current, dx, dy);
        if (squares[current])
            return { i, squares[current] };
    }
    return { };
}

bool judge::piece_attacked(const board_piece squares[], board_square square, bool turn) {

    return false;
}