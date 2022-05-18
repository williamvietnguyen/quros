#include "tests.h"
#include "attack.h"
#include "bitboard.h"
#include "defs.h"
#include "assert.h"
#include <stdio.h>

U64 test_board = 0ULL;

static void test_set_bit() {
    test_board = 0ULL;
    set_bit(&test_board, E4);
    set_bit(&test_board, A8);
    set_bit(&test_board, H1);
    assert(test_board == 0x8000001000000001);
}

static void test_test_bit() {
    test_board = 0ULL;
    set_bit(&test_board, E4);
    set_bit(&test_board, H1);
    assert(test_bit(test_board, E4) == 1);
    assert(test_bit(test_board, H2) == 0);
    assert(test_bit(test_board, H1) == 1);
    assert(test_bit(test_board, A8) == 0);
}

static void test_pop_bit() {
    test_board = 0ULL;
    set_bit(&test_board, E4);
    set_bit(&test_board, A8);
    set_bit(&test_board, H1);
    assert(test_board != 0);
    pop_bit(&test_board, E4);
    pop_bit(&test_board, A8);
    pop_bit(&test_board, H1);
    assert(test_board == 0);
}

static void test_get_square_number() {
    assert(get_square_number(RANK_4, FILE_E) == E4);
    assert(get_square_number(RANK_8, FILE_A) == A8);
    assert(get_square_number(RANK_1, FILE_H) == H1);
}

static void test_pawn_east_attacks() {
    assert(get_east_pawn_attack_mask(WHITE, E4) == 0x20000000); 
    assert(get_east_pawn_attack_mask(WHITE, H4) == 0);
    assert(get_east_pawn_attack_mask(WHITE, A4) == 0x2000000);
    assert(get_east_pawn_attack_mask(WHITE, H8) == 0);
    assert(get_east_pawn_attack_mask(WHITE, A8) == 0);

    assert(get_east_pawn_attack_mask(BLACK, E4) == 0x200000000000); 
    assert(get_east_pawn_attack_mask(BLACK, H4) == 0);
    assert(get_east_pawn_attack_mask(BLACK, A4) == 0x20000000000);
    assert(get_east_pawn_attack_mask(BLACK, H1) == 0);
    assert(get_east_pawn_attack_mask(BLACK, A1) == 0);
}

static void test_pawn_west_attacks() {
    assert(get_west_pawn_attack_mask(WHITE, G4) == 0x20000000); 
    assert(get_west_pawn_attack_mask(WHITE, H4) == 0x40000000);
    assert(get_west_pawn_attack_mask(WHITE, A4) == 0);
    assert(get_west_pawn_attack_mask(WHITE, H8) == 0);
    assert(get_west_pawn_attack_mask(WHITE, A8) == 0);

    assert(get_west_pawn_attack_mask(BLACK, G4) == 0x200000000000); 
    assert(get_west_pawn_attack_mask(BLACK, H4) == 0x400000000000);
    assert(get_west_pawn_attack_mask(BLACK, A4) == 0);
    assert(get_west_pawn_attack_mask(BLACK, H1) == 0);
    assert(get_west_pawn_attack_mask(BLACK, A1) == 0);
}

static void test_knight_attacks() {
    assert(get_knight_attack_mask(E4) == 0x28440044280000);
    assert(get_knight_attack_mask(H1) == 0x20400000000000);
    assert(get_knight_attack_mask(A1) == 0x4020000000000);
    assert(get_knight_attack_mask(A8) == 0x20400);
    assert(get_knight_attack_mask(H8) == 0x402000);
    assert(get_knight_attack_mask(B7) == 0x5080008);
    assert(get_knight_attack_mask(G7) == 0xA0100010);
    assert(get_knight_attack_mask(B2) == 0x800080500000000);
    assert(get_knight_attack_mask(G2) == 0x100010A000000000);
    assert(get_knight_attack_mask(E1) == 0x44280000000000);
    assert(get_knight_attack_mask(E8) == 0x284400);
}

static void test_king_attacks() {
    assert(get_king_attack_mask(E4) == 0x382838000000);
    assert(get_king_attack_mask(H1) == 0x40C0000000000000);
    assert(get_king_attack_mask(A1) == 0x203000000000000);
    assert(get_king_attack_mask(H8) == 0xC040);
    assert(get_king_attack_mask(A8) == 0x302);
    assert(get_king_attack_mask(A4) == 0x30203000000);
    assert(get_king_attack_mask(H4) == 0xC040C0000000);
}

static void run_bitboard_tests() {
    test_set_bit();
    test_test_bit();
    test_pop_bit();
    test_get_square_number();
    printf("Passing bitboard tests...\n");
}

static void run_attack_tests() {
    init_attacks();
    test_pawn_east_attacks();
    test_pawn_west_attacks();
    test_knight_attacks();
    test_king_attacks();
    printf("Passing attack tests...\n");
}

void run_tests() {
    printf("\nRunning tests...\n");
    run_bitboard_tests();
    run_attack_tests();
    printf("Passed all tests!\n");
}