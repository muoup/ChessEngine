#include <cstdint>
#include <map>

namespace chess {
    typedef uint8_t Piece;

    enum PieceType {
        NONE,
        PAWN,
        KNIGHT, BISHOP,
        ROOK,
        QUEEN, KING
    };

    const Piece EMPTY = 0;
    const std::map<int, PieceType> CHAR_TO_TYPE = {
            {'p', PAWN},
            {'n', KNIGHT},
            {'b', BISHOP},
            {'r', ROOK},
            {'q', QUEEN},
            {'k', KING}
    };
    const std::map<PieceType, char> TYPE_TO_CHAR = {
            {PAWN, 'p'},
            {KNIGHT, 'n'},
            {BISHOP, 'b'},
            {ROOK, 'r'},
            {QUEEN, 'q'},
            {KING, 'k'}
    };

    PieceType char_type(char c);

    Piece piece(PieceType type, bool white);
    Piece piece_fen(char c);

    bool piece_clr(Piece square);
    PieceType piece_type(Piece piece);

    bool is_empty(Piece piece);
    bool is_enemy(Piece piece, bool white);
    bool is_ally(Piece piece, bool white);

    char to_char(Piece piece);
}