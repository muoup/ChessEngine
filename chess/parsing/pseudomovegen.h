#ifndef CHESSENGINE_PSEUDOMOVEGEN_H
#define CHESSENGINE_PSEUDOMOVEGEN_H

#include <vector>
#include "../data/position.h"

namespace chess {
    namespace movegen {
        void pseudo_movegen(const board_piece squares[], position_data &position);
        void capture_comb(const board_piece squares[], const position_data& data);
    }
}

#endif
