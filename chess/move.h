#ifndef CHESSENGINE_MOVE_H
#define CHESSENGINE_MOVE_H

#include "square.h"
#include "piece.h"

#define NO_ARG
#define MOVE_PTR

#define dyn_ptr_cmd(before, after) { \
    switch (type) { \
        case NORMAL: \
            before ((StdMove*) move) after; \
            break; \
        case CAPTURE: \
            before ((CaptureMove*) move) after; \
            break; \
        case ENPASSANT: \
            before ((EnPassantMove*) move) after; \
            break; \
        case CASTLE: \
            before ((CastleMove*) move) after; \
            break; \
    } \
}

// TODO: This whole section should really be done procedurally, it works though so I'll leave it for now.
namespace chess {
    struct PositionData;

    enum MoveType {
        NORMAL,
        CAPTURE,
        CASTLE,
        ENPASSANT
    };

    class BaseMove {
    public:
        virtual void PlayMove(Piece squares[], PositionData& data) {};
        virtual void UndoMove(Piece squares[], PositionData& data) {};
    };

    class StdMove : BaseMove {
    public:
        StdMove(Square from, Square to,
                Piece promotion = EMPTY) : from(from), to(to), promotion(promotion) {};

        void PlayMove(Piece squares[], PositionData& data) override;
        void UndoMove(Piece squares[], PositionData& data) override;

    protected:
        Square from;
        Square to;
        Piece promotion;
    };

    class CaptureMove : StdMove {
    public:
        CaptureMove(Square from, Square to, Piece capture,
                    Piece promotion = EMPTY) : StdMove(from, to, promotion), captured(capture) {};

        void PlayMove(Piece squares[], PositionData& data) override;
        void UndoMove(Piece squares[], PositionData& data) override;

    protected:
        Piece captured;
    };

    class EnPassantMove : StdMove {
    public:
        EnPassantMove(Square from, Square to,
                      Square enpassantSquare) : StdMove(from, to, EMPTY), enpassantSquare(enpassantSquare) {};

        void PlayMove(Piece squares[], PositionData& data) override;
        void UndoMove(Piece squares[], PositionData& data) override;

    private:
        Square enpassantSquare;
    };

    class CastleMove : BaseMove {
    public:
        CastleMove(Square kingSquare, Square rookSquare) : kingSquare(kingSquare), rookSquare(rookSquare) {};

        void PlayMove(Piece squares[], PositionData& data) override;
        void UndoMove(Piece squares[], PositionData& data) override;

    private:
        Square kingSquare;
        Square rookSquare;
    };

    class Move {
    public:
        Move(void* move, MoveType type) : type(type), move(move) {}
        ~Move();

        void PlayMove(Piece squares[], PositionData& data);
        void UndoMove(Piece squares[], PositionData& data);

    private:
        void* move;
        MoveType type;
    };

    Move&& std_move(const Piece squares[], Square from, Square to, Piece promotion = EMPTY);
    Move&& capture_move(Square from, Square to, Piece captured, Piece promotion = EMPTY);
    Move&& castle_move(Square kingSquare, Square rookSquare);
    Move&& enpassant_move(Square from, Square to, Square enpassantSquare);
}

#endif