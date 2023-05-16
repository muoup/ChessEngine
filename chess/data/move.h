#ifndef CHESSENGINE_MOVE_H
#define CHESSENGINE_MOVE_H

#include <string>
#include <iostream>
#include <memory>
#include "square.h"
#include "piece.h"

namespace chess {
    struct position_data;
    struct board_move;

    enum move_type {
        STANDARD,
        CAPTURE,
        CASTLE,
        EN_PASSANT
    };

    struct static_move_data {
        move_type type;
        void (*play)(const board_move& move, board_piece squares[], position_data& data);
        void (*undo)(board_piece squares[], const position_data& data);
        std::string (*to_string)(const board_move& move);
    };

    struct board_move {
        const static_move_data* method_refs;

        board_square from, to, en_passant;
        board_piece captured_piece, promotion;
    };

    namespace move_functions {
        void std_play(const board_move&, board_piece[], position_data&);
        void std_undo(board_piece[], const position_data&);
        std::string std_to_string(const board_move&);
        void capture_play(const board_move&, board_piece[], position_data&);
        void capture_undo(board_piece[], const position_data&);
        std::string capture_to_string(const board_move&);
        void en_passant_play(const board_move&, board_piece[], position_data&);
        void en_passant_undo(board_piece[], const position_data&);
        std::string en_passant_to_string(const board_move&);
        void castle_play(const board_move&, board_piece[], position_data&);
        void castle_undo(board_piece[], const position_data&);
        std::string castle_to_string(const board_move&);
    }

    // I feel really stupid to have done all of this when like three switch statements would have sufficed.
    // However I think this is a bit more elegant, and I have put too much effort into this to scrap it.
    const static_move_data move_data[4] = {
        { STANDARD, move_functions::std_play, move_functions::std_undo, move_functions::std_to_string },
        { CAPTURE, move_functions::capture_play, move_functions::capture_undo, move_functions::capture_to_string },
        { CASTLE, move_functions::castle_play, move_functions::castle_undo, move_functions::castle_to_string },
        { EN_PASSANT, move_functions::en_passant_play, move_functions::en_passant_undo, move_functions::en_passant_to_string }
    };

    std::string to_string(const board_move& move);

    board_move std_move(const board_piece squares[], const board_square& from, const board_square& to, PieceType promotion = NONE);
    board_move capture_move(const board_square& from, const board_square& to, const board_piece& capture, PieceType promotion = NONE);

    board_move ptwo_move(const board_square &from, const board_square &to);
    board_move en_passant_move(const board_square& from, const board_square& to, const board_square& en_passant_square);
    board_move castle_move(const board_square& king_square, const board_square& rook_square);
}

#endif