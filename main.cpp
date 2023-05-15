#include "chess/board.h"

int main() {
    chess::Board board("4k2r/8/8/8/8/8/8/4K2R w Kk - 0 1");

    chess::Move move = chess::std_move(board.GetSquares(), "h1", "h8");
    board.PlayMove(move);
    board.Print();
    board.UndoMove();
    board.Print();

//    board.PlayMove(testMove);
//    board.Print();
//    board.UndoMove();
//    board.Print();

    return 0;
}
