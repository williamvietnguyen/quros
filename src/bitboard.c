#include "bitboard.h"
#include "defs.h"
#include <stdio.h>
#include <assert.h>

int test_bit(U64 bitboard, int square) {
    assert(square < NUM_SQ && square >= 0);
    return (bitboard & (1ULL << square)) ? 1 : 0;
}

void set_bit(U64* bitboard, int square) {
    assert(square < NUM_SQ && square >= 0);
    *bitboard |= (1ULL << square);
}

void pop_bit(U64* bitboard, int square) {
    assert(test_bit(*bitboard, square));
    *bitboard ^= 1ULL << square;
}

int get_square_number(int rank, int file) {
    return rank * 8 + file;
}

void print_bitboard(U64 bitboard) {
    /* lsb: a8, msb: h1 */
    for (int rank = RANK_8; rank < RANKS; rank++) {
        for (int file = FILE_A; file < FILES; file++) {
            if (!file) {
                printf(" %d   ", 8 - rank);
            }
            printf(" %d ", test_bit(bitboard, get_square_number(rank, file)));
        }
        printf("\n");
    }

    printf("\n");
    printf("      a  b  c  d  e  f  g  h");
    printf("\n\n");
    printf("Bitboard: 0x%llX \n\n", bitboard);
}