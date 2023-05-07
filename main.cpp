#include "chess/board.h"

int main() {
    chess::Board board;

    chess::Move testMove = chess::std_move(board.GetSquares(), chess::square("e2"), chess::square("e4"));

    board.PlayMove(testMove);
    board.print();

    return 0;
}
