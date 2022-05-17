#include "attack.h"
#include "bb.h"
#include "defs.h"

U64 pawn_attacks[COLORS][NUM_SQ];

U64 get_pawn_attack_mask(int color, int square) {
    return pawn_attacks[color][square];
}

static U64 pawn_attacks_mask(int square, int color) {
    U64 mask = 0ULL;
    if (color == WHITE) {
        if (get_rank(square) == RANK_8) {
            return mask;
        }
        if (get_file(square) != FILE_A) {
            set_bit(&mask, square - 9);
        }
        if (get_file(square) != FILE_H) {
            set_bit(&mask, square - 7);
        }
    } else {
        if (get_rank(square) == RANK_1) {
            return mask;
        }
        if (get_file(square) != FILE_A) {
            set_bit(&mask, square + 7);
        }
        if (get_file(square) != FILE_H) {
            set_bit(&mask, square + 9);
        }
    }
    return 0ULL | mask;
}

static void init_pawn_attacks() {
    for (int rank = 0; rank < RANKS; rank++) {
        for (int file = 0; file < FILES; file++) {
            int square = get_square_number(rank, file);
            pawn_attacks[WHITE][square] = pawn_attacks_mask(square, WHITE);
            pawn_attacks[BLACK][square] = pawn_attacks_mask(square, BLACK);
        }
    }
}

void init_attacks() {
    init_pawn_attacks();
}