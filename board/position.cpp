//
// Created by zbv11 on 27-Apr-23.
//

#include "position.h"

using namespace posd;

PositionData* posd::std_pos(Square from, Square to, Piece promotion) {
    MoveType moveType = NORMAL;

    Move move = {from, to, moveType};

    auto* pos = new PositionData();
    pos->move = move;

    // TODO: Generate legal moves

    return pos;
}

PositionData* posd::castle(Square kingSquare, Square rookSquare) {

}