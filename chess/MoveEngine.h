#ifndef CHESSENGINE_MOVEENGINE_H
#define CHESSENGINE_MOVEENGINE_H

#include <vector>
#include "position.h"

namespace chess {
    void psuedo_movegen(const Piece squares[], const PositionData& data);
    void legal_movegen(const Piece squares[], const PositionData& data);
    void capture_comb(const Piece squares[], const PositionData& data);
}

#endif
