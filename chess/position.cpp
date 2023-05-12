//
// Created by zbv11 on 27-Apr-23.
//

#include "position.h"

using namespace chess;

bool chess::has_castling_rights(const PositionData &data, CastlingType type) {
    return data.dataBits & (1 << type);
}

void chess::set_castling_rights(PositionData &data, CastlingType type, bool value) {
    if (value) data.dataBits |= (1 << type);
    else data.dataBits &= ~(1 << type);
}

void chess::bitmask_castling_rights(PositionData &data, uint8_t mask, bool value) {
    if (value) data.dataBits |= mask;
    else data.dataBits &= ~mask;
}

void PositionData::AddMove(Move move) {
    pseudoLegalMoves.push_back(move);
}

DataBits chess::create_bits(bool turn, const bool castlingRights[4]) {
    return castlingRights[0]
       | (castlingRights[1] << 1)
       | (castlingRights[2] << 2)
       | (castlingRights[3] << 3)
       | (turn << 4);
}

bool chess::turn(const PositionData &data) {
    return data.dataBits & 0b10000;
}

void chess::set_turn(PositionData &data, bool value) {
    if (value) data.dataBits |= 0b10000;
    else data.dataBits &= ~0b10000;
}