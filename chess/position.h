#ifndef CHESSENGINE_POSITION_H
#define CHESSENGINE_POSITION_H

#include <vector>
#include "move.h"

namespace chess {
    typedef uint8_t DataBits;

    enum CastlingType {
        WHITE_QUEEN_SIDE,
        WHITE_KING_SIDE,
        BLACK_QUEEN_SIDE,
        BLACK_KING_SIDE
    };

    struct PositionData {
        Move* move;
        std::vector<Move>& pseudoLegalMoves;

        DataBits dataBits;
        Square enPassant;
    };

    bool has_castling_rights(const PositionData& data, CastlingType type);
    void set_castling_rights(PositionData& data, CastlingType type, bool value);
    void bitmask_castling_rights(PositionData& data, uint8_t mask, bool value);

    DataBits create_bits(bool turn, const bool castlingRights[4]);

    bool turn(const PositionData& data);
    void set_turn(PositionData& data, bool value);
}

#endif