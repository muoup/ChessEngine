#include <cstdint>
#include <map>

namespace chess {
    enum PieceType {
        NONE,
        PAWN,
        KNIGHT, BISHOP,
        ROOK,
        QUEEN, KING
    };

    struct Piece {
        uint8_t piece;

        Piece() = default;
        Piece(const Piece& piece) : piece(piece.piece) {}
        Piece(uint8_t piece) : piece(piece) {}
        Piece(char c);
        Piece(PieceType type, bool white) {
            if (type != NONE)
                piece = (type << 1) | white;
        }

        operator uint8_t() const { return piece; }
        operator int() const { return piece; }
        operator char() const;
        operator bool() const { return piece != 0; }
    };

    const Piece EMPTY = Piece();

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

    bool piece_clr(const Piece& piece);
    PieceType piece_type(const Piece& piece);

    bool is_empty(Piece piece);
    bool is_enemy(const Piece& piece, bool white);
    bool is_ally(const Piece& piece, bool white);
}