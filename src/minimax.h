#ifndef MINMAX
#define MINMAX

#include "board_rep.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <limits.h>
#include <vector>

struct Move
{
	int oldrow;
	int oldcol;
	int newrow;
	int newcol;
};

int maxi(ChessBoard B, int depth); // White
int mini(ChessBoard B, int depth); // Black

std::vector<Move> gen_all_next_moves(ChessBoard B, int color);

#endif