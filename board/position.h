//
// Created by zbv11 on 27-Apr-23.
//

#ifndef CHESSENGINE_POSITION_H
#define CHESSENGINE_POSITION_H

#include <vector>
#include <cstdint>
#include "data.h"

namespace posd {
    struct PositionData {
        Move move;

        std::vector<Move> legalMoves;
    };

    PositionData* std_pos(Square from, Square to, Piece promotion);
    PositionData* enPassant(Square from, Square to);
    PositionData* castle(Square kingSquare, Square rookSquare);
}

#endif //CHESSENGINE_POSITION_H
