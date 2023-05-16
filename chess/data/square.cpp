#include "square.h"

using namespace chess;

board_square chess::shift(const board_square& origin, int8_t dx, int8_t dy) {
    if (origin.rank() + dy > 7 || origin.rank() + dy < 0 ||
        origin.file() + dx > 7 || origin.file() + dx < 0)
        return NULL_SQUARE;

    return {static_cast<uint8_t>(origin.file() + dx), static_cast<uint8_t>(origin.rank() + dy)};
}

uint8_t board_square::rank() const {
    return (data >> 3) & 0b111;
}

uint8_t board_square::file() const {
    return data & 0b111;
}

board_square::operator std::string() const {
    return std::string(1, 'a' + file()).append(1, '1' + rank());
}

board_square board_square::operator+(const board_square& other) const {
    return {(data + other.data) ^ 0x80 };
}

bool board_square::valid() const {
    return data != NULL_SQUARE;
}

bool board_square::invalid() const {
    return data == NULL_SQUARE;
}