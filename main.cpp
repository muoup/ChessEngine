#include "chess/board.h"
#include "chess/parsing/legalcheck.h"

int main() {
    chess::board board("4k2r/8/8/8/8/8/8/4K2R w Kk - 0 1");

    chess::judge::piece_attacked(board, chess::board_square("e1"), true);

    return 0;
}