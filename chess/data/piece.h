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

    struct board_piece {
        uint8_t piece;

        constexpr board_piece() : piece(0) {};
        constexpr board_piece(uint8_t piece) : piece(piece) {}
        constexpr board_piece(const board_piece& piece) : piece(piece.piece) {}
        constexpr board_piece(PieceType type, bool white) {
            if (type == NONE) {
                piece = 0;
                return;
            }

            piece = (type << 1) | white;
        }

        board_piece(char c);

        constexpr operator uint8_t() const { return piece; }
        constexpr operator int() const { return piece; }

        operator bool() const;
        operator char() const;
    };

    const board_piece EMPTY = board_piece();

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

    bool piece_clr(const board_piece& piece);
    PieceType piece_type(const board_piece& piece);

    bool is_enemy(const board_piece& piece, bool white);
    bool is_ally(const board_piece& piece, bool white);
}