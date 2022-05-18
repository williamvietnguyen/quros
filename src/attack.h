#ifndef ATTACK_H_
#define ATTACK_H_

#include "bb.h"

U64 get_west_pawn_attack_mask(int color, int square);
U64 get_east_pawn_attack_mask(int color, int square);
U64 get_knight_attack_mask(int square);
void init_attacks();

#endif