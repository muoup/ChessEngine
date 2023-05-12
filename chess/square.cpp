#include "square.h"

using namespace chess;

chess::Square chess::shift(const Square& origin, int8_t dx, int8_t dy) {
    if (origin.rank() + dy > 7 || origin.rank() + dy < 0 ||
        origin.file() + dx > 7 || origin.file() + dx < 0)
        return 0;

    return { static_cast<uint8_t>(origin.file() + dx), static_cast<uint8_t>(origin.rank() + dy) };
}

uint8_t Square::rank() const {
    return (square >> 3) & 0b111;
}

uint8_t Square::file() const {
    return square & 0b111;
}

Square::operator uint8_t() const {
    return square ^ 0x80;
}

Square::operator std::string() const {
    return std::string(1, 'a' + file()).append(1, '1' + rank());
}

Square Square::operator+(const Square& other) const {
    return {(square + other.square) ^ 0x80 };
}