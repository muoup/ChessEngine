#include <cstdint>
#include <unordered_map>

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

        constexpr Piece() : piece(0) {};
        constexpr Piece(uint8_t piece) : piece(piece) {}
        constexpr Piece(const Piece& piece) : piece(piece.piece) {}
        constexpr Piece(PieceType type, bool white) {
            if (type == NONE) {
                piece = 0;
                return;
            }

            piece = (type << 1) | white;
        }

        Piece(char c);

        constexpr operator uint8_t() const { return piece; }
        constexpr operator int() const { return piece; }

        operator bool() const;
        operator char() const;
    };

    const Piece EMPTY = Piece();

    const std::unordered_map<int, PieceType> CHAR_TO_TYPE = {
            {'p', PAWN},
            {'n', KNIGHT},
            {'b', BISHOP},
            {'r', ROOK},
            {'q', QUEEN},
            {'k', KING}
    };
    const std::unordered_map<PieceType, char> TYPE_TO_CHAR = {
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

    bool is_enemy(const Piece& piece, bool white);
    bool is_ally(const Piece& piece, bool white);
}