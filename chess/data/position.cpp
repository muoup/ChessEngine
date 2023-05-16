//
// Created by zbv11 on 27-Apr-23.
//

#include "position.h"

using namespace chess;

bool chess::has_castling_rights(const position_data &data, castling_type type) {
    return data.dataBits & (1 << type);
}

void chess::set_castling_rights(position_data &data, castling_type type, bool value) {
    if (value) data.dataBits |= (1 << type);
    else data.dataBits &= ~(1 << type);
}

void chess::bitmask_castling_rights(position_data &data, data_bits mask, bool value) {
    if (value) data.dataBits |= mask;
    else data.dataBits &= ~mask;
}

void position_data::add_move(const board_move& move) {
    pseudo_legal_moves.push_back(move);
}

data_bits chess::create_bits(bool turn, const bool castling_rights[4]) {
    return castling_rights[0]
           | (castling_rights[1] << 1)
           | (castling_rights[2] << 2)
           | (castling_rights[3] << 3)
           | (turn << 4);
}

bool chess::turn(const position_data &data) {
    return data.dataBits & 0b10000;
}

void chess::set_turn(position_data &data, bool value) {
    if (value) data.dataBits |= 0b10000;
    else data.dataBits &= ~0b10000;
}