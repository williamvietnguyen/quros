#include <stdio.h>
#include <assert.h>
#include "bb.h"

int test_bit(U64 bitboard, int square) {
    assert(square < 64 && square >= 0);
    return (bitboard & (1ULL << square)) ? 1 : 0;
}

void set_bit(U64* bitboard, int square) {
    assert(square < 64 && square >= 0);
    *bitboard |= (1ULL << square);
}

void pop_bit(U64* bitboard, int square) {
    // bit must be set to be popped
    assert(test_bit(*bitboard, square));
    *bitboard ^= 1ULL << square;
}

void print_bitboard(U64 bitboard) {
    // lsb: a8, msb: h1
    for (int rank = 0; rank < 8; rank++) {
        for (int file = 0; file < 8; file++) {
            if (!file) {
                printf(" %d   ", 8 - rank);
            }
            printf(" %d ", test_bit(bitboard, rank * 8 + file));
        }
        printf("\n");
    }
    printf("\n");
    printf("      a  b  c  d  e  f  g  h");
    printf("\n\n");
    printf("Bitboard: %llu \n\n", bitboard);
}