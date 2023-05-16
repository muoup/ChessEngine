#include "chess/board.h"

int main() {
    //chess::Board board("4k2r/8/8/8/8/8/8/4K2R w Kk - 0 1");
    chess::Board board;

    board.play_move(chess::std_move(board, "e2", "e4"));
    board.play_move(chess::std_move(board, "h7", "h5"));
    board.play_move(chess::std_move(board, "e4", "e5"));
    board.play_move(chess::std_move(board, "d7", "d5", chess::NONE, "d6"));

    board.print();
    board.pm_print();

    return 0;
}