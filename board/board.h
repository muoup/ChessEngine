#ifndef CHESSENGINE_BOARD_H
#define CHESSENGINE_BOARD_H

#include <stack>
#include <memory>
#include <vector>

struct PositionData;
struct Move;

class Board {
public:
    Board();

    void PushMove(Move move);
    Move PopMove();

    void PlayMove(Move move);
    Move UndoMove();
private:
    std::unique_ptr<std::stack<PositionData>> positionStack;
};


#endif //CHESSENGINE_BOARD_H
