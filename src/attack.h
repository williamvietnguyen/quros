#ifndef ATTACK_H_
#define ATTACK_H_

#include "bb.h"

U64 get_pawn_attack_mask(int color, int square);
void init_attacks();

#endif