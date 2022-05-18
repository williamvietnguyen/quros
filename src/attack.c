#include "attack.h"
#include "bb.h"
#include "defs.h"

U64 west_pawn_attacks[COLORS][NUM_SQ];
U64 east_pawn_attacks[COLORS][NUM_SQ];
U64 knight_attacks[NUM_SQ];

U64 get_west_pawn_attack_mask(int color, int square) {
    return west_pawn_attacks[color][square];
}

U64 get_east_pawn_attack_mask(int color, int square) {
    return east_pawn_attacks[color][square];
}

U64 get_knight_attack_mask(int square) {
    return knight_attacks[square];
}

/* Gets the pawn attacks for direction and color */
static U64 white_pawn_east_attack(U64 b) {return (b & NOT_H_FILE) >> 7;}
static U64 white_pawn_west_attack(U64 b) {return (b & NOT_A_FILE) >> 9;}
static U64 black_pawn_east_attack(U64 b) {return (b & NOT_H_FILE) << 9;}
static U64 black_pawn_west_attack(U64 b) {return (b & NOT_A_FILE) << 7;}

static void init_pawn_attacks_masks() {
    for (int rank = 0; rank < RANKS; rank++) {
        for (int file = 0; file < FILES; file++) {
            int square = get_square_number(rank, file);
            U64 b = 0ULL;
            set_bit(&b, square);
            west_pawn_attacks[WHITE][square] = white_pawn_west_attack(b);
            east_pawn_attacks[WHITE][square] = white_pawn_east_attack(b);
            west_pawn_attacks[BLACK][square] = black_pawn_west_attack(b);
            east_pawn_attacks[BLACK][square] = black_pawn_east_attack(b);
        }
    }
}

/* Gets a single knight jumping square */
static U64 no_no_ea(U64 b) {return (b & NOT_H_FILE ) << 17;}
static U64 no_ea_ea(U64 b) {return (b & NOT_GH_FILE) << 10;}
static U64 so_ea_ea(U64 b) {return (b & NOT_GH_FILE) >>  6;}
static U64 so_so_ea(U64 b) {return (b & NOT_H_FILE ) >> 15;}
static U64 no_no_we(U64 b) {return (b & NOT_A_FILE ) << 15;}
static U64 no_we_we(U64 b) {return (b & NOT_AB_FILE) <<  6;}
static U64 so_we_we(U64 b) {return (b & NOT_AB_FILE) >> 10;}
static U64 so_so_we(U64 b) {return (b & NOT_A_FILE ) >> 17;}

static void init_knight_attacks_masks() {
    for (int rank = 0; rank < RANKS; rank++) {
        for (int file = 0; file < FILES; file++) {
            int square = get_square_number(rank, file);
            U64 b = 0ULL;
            set_bit(&b, square);
            U64 mask = 0ULL;
            mask |= no_no_ea(b);
            mask |= no_ea_ea(b);
            mask |= so_ea_ea(b);
            mask |= so_so_ea(b);
            mask |= no_no_we(b);
            mask |= no_we_we(b);
            mask |= so_we_we(b);
            mask |= so_so_we(b);
            knight_attacks[square] = mask;
        }
    }
}

void init_attacks() {
    init_pawn_attacks_masks();
    init_knight_attacks_masks();
}