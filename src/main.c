#include "bb.h"
#include <stdio.h>

int main(int argc, char** argv) {
    U64 board = 0ULL;
    set_bit(&board, e2);
    print_bitboard(board);
}