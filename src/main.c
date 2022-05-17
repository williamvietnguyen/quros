#include "attack.h"
#include "bb.h"
#include "defs.h"
#include <stdio.h>

int main(int argc, char** argv) {
    init_attacks();
    U64 board = 0ULL;
    int bit = E4;
    set_bit(&board, bit);
    print_bitboard(board);
    print_bitboard(get_pawn_attack_mask(BLACK, bit));
}