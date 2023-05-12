#include "chess/board.h"

int main() {
    chess::Board board("8/4k3/8/8/8/3B1N2/2K5/2R5 w - - 0 1");

    chess::Move testMove = chess::std_move(board.GetSquares(), "e2", "e4");

//    board.PlayMove(testMove);
//    board.Print();
//    board.UndoMove();
//    board.Print();

    return 0;
}
