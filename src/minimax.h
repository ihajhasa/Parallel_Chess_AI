#ifndef MINIMAX_H
#define MINIMAX_H

#include <math.h>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <limits.h>
#include <vector>
#include <sstream>
#include <string>
#include <cstring>	
#include "board_rep.h"
#include "gen_moves.h"

Best_Move Min_Iteration (ChessBoard board, int depth, Move move, int color);

Best_Move Max_Iteration (ChessBoard board, int depth, Move move, int color);


class MiniMax
{
public:
    // std::vector<Particle> particles;
    // std::vector<Particle> newParticles;
    // std::unique_ptr<INBodySimulator> nbodySimulator;

    // List of variables that need to be global across class (if any)

    Move Generate_Next(ChessBoard board, int depth, int color);

    // void print_move(ChessBoard board, Move move);
};

#endif
