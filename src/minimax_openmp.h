#ifndef MINIMAX_OPENMP
#define MINIMAX_OPENMP

#include <math.h>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <limits.h>
#include <vector>
#include <sstream>
#include <string>
#include <cstring>	
#include "gen_moves.h"


class MiniMaxParallel
{
	public: 
		Move Generate_Next(ChessBoard board, int depth, int color);
    	void print_move(ChessBoard board, Move move);
};

#endif