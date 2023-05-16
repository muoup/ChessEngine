#ifndef CHESSENGINE_POSITION_H
#define CHESSENGINE_POSITION_H

#include <vector>
#include "move.h"

namespace chess {
    typedef uint8_t data_bits;

    const data_bits WHITE_CASTLE_MASK = 0b0011;
    const data_bits BLACK_CASTLE_MASK = 0b1100;

    enum castling_type {
        WHITE_KING_SIDE,
        WHITE_QUEEN_SIDE,
        BLACK_KING_SIDE,
        BLACK_QUEEN_SIDE,
    };

    struct position_data {
        board_move prev_move;
        std::vector<board_move> pseudo_legal_moves;

        data_bits dataBits;
        board_square en_passant;

        void add_move(const board_move& move);
    };

    bool has_castling_rights(const position_data& data, castling_type type);
    void set_castling_rights(position_data& data, castling_type type, bool value);
    void bitmask_castling_rights(position_data& data, data_bits mask, bool value);

    data_bits create_bits(bool turn, const bool castling_rights[4]);

    bool turn(const position_data& data);
    void set_turn(position_data& data, bool value);
}

#endif