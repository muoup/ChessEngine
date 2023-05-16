#ifndef CHESSENGINE_LEGALCHECK_H
#define CHESSENGINE_LEGALCHECK_H

#include "../data/position.h"

namespace chess {
    namespace judge {
        bool piece_attacked(const board_piece squares[], board_square square, bool turn);
    }
}

#endif