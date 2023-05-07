#ifndef CHESSENGINE_SQUARE_H
#define CHESSENGINE_SQUARE_H

#include <cstdint>
#include <string>

namespace chess {
    typedef uint8_t Square;

    Square square(uint8_t x, uint8_t y);
    Square square(const std::string& str);

    Square shift(Square square, uint8_t dx, uint8_t dy);

    uint8_t rank(Square square);
    uint8_t file(Square square);

    std::string to_string(Square square);
}

#endif
