#ifndef CHESSENGINE_SQUARE_H
#define CHESSENGINE_SQUARE_H

#include <cstdint>
#include <string>

namespace chess {
    struct board_square {
        uint8_t data;

        constexpr board_square() : data(0) { }
        constexpr board_square(uint8_t square) : data(square) { }
        constexpr board_square(int square) : data(square) { }
        constexpr board_square(uint8_t x, uint8_t y) : data(0x80 | (y << 3) | x) { }
        constexpr board_square(const char* str) : data(0x80 | ((str[1] - '1') << 3) | (str[0] - 'a')) {}

        board_square(const board_square& square) : data(square.data) { }

        constexpr operator uint8_t() const {
            return data ^ 0x80;
        }

        operator std::string() const;

        board_square operator +(const board_square& other) const;

        bool operator ==(const board_square& other) const {
            return data == other.data;
        }
        bool operator ==(uint8_t other) const {
            return data == other;
        }

        bool valid() const;
        bool invalid() const;

        uint8_t rank() const;
        uint8_t file() const;
    };

    board_square shift(const board_square& square, int8_t dx, int8_t dy);

    constexpr board_square NULL_SQUARE = board_square();

    constexpr board_square W_K_ROOK = "a1";
    constexpr board_square W_Q_ROOK = "h1";
    constexpr board_square B_K_ROOK = "a8";
    constexpr board_square B_Q_ROOK = "h8";
}

#endif
