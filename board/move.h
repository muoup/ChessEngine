//
// Created by zbv11 on 27-Apr-23.
//

#ifndef CHESSENGINE_MOVE_H
#define CHESSENGINE_MOVE_H

#include <cstdint>
#include "position.h"

class BaseMove {
public:
    virtual void PlayMove() = 0;
    virtual void UndoMove() = 0;
};

class StdMove : BaseMove {
public:
    StdMove(posd::Square from, posd::Square to,
            posd::Piece promotion = posd::EMPTY) : from(from), to(to), promotion(promotion) {};

    void PlayMove() override;
    void UndoMove() override;

protected:
    posd::Square from;
    posd::Square to;
    posd::Piece promotion;
};

class CaptureMove : StdMove {
public:
    CaptureMove(posd::Square from, posd::Square to, posd::Piece capture,
                posd::Piece promotion = posd::EMPTY) : StdMove(from, to, promotion), captured(capture) {};

    void PlayMove() override;
    void UndoMove() override;

protected:
    posd::Piece captured;
};

class EnPassantMove : StdMove {
public:
    EnPassantMove(posd::Square from, posd::Square to,
                  posd::EnPassantData data) : StdMove(from, to, posd::EMPTY), data(data) {};

    void PlayMove() override;
    void UndoMove() override;

private:
    posd::EnPassantData data;
};

class CastleMove : BaseMove {
public:
    CastleMove(posd::Square kingSquare, posd::Square rookSquare) : kingSquare(kingSquare), rookSquare(rookSquare) {};

    void PlayMove() override;
    void UndoMove() override;

private:
    posd::Square kingSquare;
    posd::Square rookSquare;
};

#endif //CHESSENGINE_MOVE_H
