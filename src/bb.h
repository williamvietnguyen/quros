#ifndef BB_H_
#define BB_H_

#include <stdint.h>

typedef uint64_t U64;

int test_bit(U64 bitboard, int square);
void set_bit(U64* bitboard, int square);
void pop_bit(U64* bitboard, int square);
int get_square_number(int rank, int file);
int get_rank(int square);
int get_file(int square);
void print_bitboard(U64 bitboard);

#endif