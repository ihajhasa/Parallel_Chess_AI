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



Best_Move parallel_max(ChessBoard board, int depth, Move move, int color);
Best_Move parallel_min(ChessBoard board, int depth, Move move, int color);

class MiniMaxParallel
{
	public: 
		Move Generate_Next(ChessBoard board, int depth, int color);
    	// void print_move(ChessBoard board, Move move);
};

#endif