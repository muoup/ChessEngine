#ifndef CHESSENGINE_SQUARE_H
#define CHESSENGINE_SQUARE_H

#include <cstdint>
#include <string>

namespace chess {
    struct Square {
        uint8_t square;

        Square() : Square(0) { }
        Square(const Square& square) : Square(square.square) { }
        Square(uint8_t square) : square(square) { }
        Square(int square) : Square(static_cast<uint8_t>(square)) { }
        Square(uint8_t x, uint8_t y) : Square(0x80 | (y << 3) | x) { }
        Square(const std::string& str) : Square(str[0] - 'a', str[1] - '1') { }
        Square(const char* str) : Square(std::string(str)) { }

        operator uint8_t() const;
        operator std::string() const;

        Square& operator =(const Square& square) = default;
        Square operator +(const Square& other) const;

        uint8_t rank() const;
        uint8_t file() const;
    };

    Square shift(const Square& square, int8_t dx, int8_t dy);
}

#endif
