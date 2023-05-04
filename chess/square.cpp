#include "square.h"

// TODO: Maybe error-handle these functions, but I don't think it's necessary, as that should be implementation's job.

chess::Square chess::square(uint8_t x, uint8_t y) {
    return (y << 3) | x;
}

chess::Square chess::shift(Square origin, uint8_t dx, uint8_t dy) {
    return origin + square(dx, dy);
}

uint8_t chess::rank(Square square) {
    return square >> 3;
}

uint8_t chess::file(Square square) {
    return square & 0b111;
}