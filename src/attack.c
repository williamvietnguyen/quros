#include "attack.h"
#include "bitboard.h"
#include "defs.h"

U64 west_pawn_attacks[COLORS][NUM_SQ];
U64 east_pawn_attacks[COLORS][NUM_SQ];
U64 knight_attacks[NUM_SQ];
U64 king_attacks[NUM_SQ];

const U64 NOT_A_FILE = 0xFEFEFEFEFEFEFEFE;
const U64 NOT_AB_FILE = 0xFCFCFCFCFCFCFCFC;
const U64 NOT_H_FILE = 0x7F7F7F7F7F7F7F7F;
const U64 NOT_GH_FILE = 0x3F3F3F3F3F3F3F3F;

U64 get_west_pawn_attack_mask(int color, int square) {
    return west_pawn_attacks[color][square];
}

U64 get_east_pawn_attack_mask(int color, int square) {
    return east_pawn_attacks[color][square];
}

U64 get_knight_attack_mask(int square) {
    return knight_attacks[square];
}

U64 get_king_attack_mask(int square) {
    return king_attacks[square];
}

/* Gets the pawn attacks for direction and color */
static U64 white_pawn_east_attack(U64 b) {return (b & NOT_H_FILE) >> 7;}
static U64 white_pawn_west_attack(U64 b) {return (b & NOT_A_FILE) >> 9;}
static U64 black_pawn_east_attack(U64 b) {return (b & NOT_H_FILE) << 9;}
static U64 black_pawn_west_attack(U64 b) {return (b & NOT_A_FILE) << 7;}

/* Reference: https://www.chessprogramming.org/Pawn_Attacks_(Bitboards) */
static void init_pawn_attacks_masks() {
    for (int square = 0; square < NUM_SQ; square++) {
        U64 b = 0ULL;
        set_bit(&b, square);
        west_pawn_attacks[WHITE][square] = white_pawn_west_attack(b);
        east_pawn_attacks[WHITE][square] = white_pawn_east_attack(b);
        west_pawn_attacks[BLACK][square] = black_pawn_west_attack(b);
        east_pawn_attacks[BLACK][square] = black_pawn_east_attack(b);
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

/* Reference: https://www.chessprogramming.org/Knight_Pattern */
static void init_knight_attacks_masks() {
    for (int square = 0; square < NUM_SQ; square++) {
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

static U64 nw_king_attack(U64 b) {return (b & NOT_A_FILE) >> 9;}
static U64 nn_king_attack(U64 b) {return b >> 8;}
static U64 ne_king_attack(U64 b) {return (b & NOT_H_FILE) >> 7;}
static U64 ww_king_attack(U64 b) {return (b & NOT_A_FILE) >> 1;}
static U64 ee_king_attack(U64 b) {return (b & NOT_H_FILE) << 1;}
static U64 sw_king_attack(U64 b) {return (b & NOT_A_FILE) << 7;}
static U64 ss_king_attack(U64 b) {return b << 8;}
static U64 se_king_attack(U64 b) {return (b & NOT_H_FILE) << 9;}

static void init_king_attacks_masks() {
    for (int square = 0; square < NUM_SQ; square++) {
        U64 b = 0ULL;
        set_bit(&b, square);
        U64 mask = 0ULL;
        mask |= nw_king_attack(b);
        mask |= nn_king_attack(b);
        mask |= ne_king_attack(b);
        mask |= ww_king_attack(b);
        mask |= ee_king_attack(b);
        mask |= sw_king_attack(b);
        mask |= ss_king_attack(b);
        mask |= se_king_attack(b);
        king_attacks[square] = mask;
    }
}

void init_attacks() {
    init_pawn_attacks_masks();
    init_knight_attacks_masks();
    init_king_attacks_masks();
}