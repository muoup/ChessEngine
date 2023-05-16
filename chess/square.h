#ifndef CHESSENGINE_SQUARE_H
#define CHESSENGINE_SQUARE_H

#include <cstdint>
#include <string>

namespace chess {
    struct Square {
        uint8_t square;

        constexpr Square() : square(0) { }
        constexpr Square(uint8_t square) : square(square) { }
        constexpr Square(int square) : square(square) { }
        constexpr Square(uint8_t x, uint8_t y) : Square(0x80 | (y << 3) | x) { }
        constexpr Square(const char* str) : square(0x80 | ((str[1] - '1') << 3) | (str[0] - 'a')) {}

        Square(const Square& square) : Square(square.square) { }

        constexpr operator uint8_t() const {
            return square ^ 0x80;
        }

        operator std::string() const;

        Square& operator =(const Square& square) = default;
        Square operator +(const Square& other) const;

        bool operator ==(const Square& other) const {
            return square == other.square;
        }
        bool operator ==(uint8_t other) const {
            return square == other;
        }

        bool valid() const;
        bool invalid() const;

        uint8_t rank() const;
        uint8_t file() const;
    };

    Square shift(const Square& square, int8_t dx, int8_t dy);

    constexpr Square NULL_SQUARE = Square();

    constexpr Square W_K_ROOK = "a1";
    constexpr Square W_Q_ROOK = "h1";
    constexpr Square B_K_ROOK = "a8";
    constexpr Square B_Q_ROOK = "h8";
}

#endif
