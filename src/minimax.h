#ifndef MINIMAX_H
#define MINIMAX_H

#include <math.h>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <limits.h>
#include <vector>

struct Pos
{
	int row;
	int col;
}

struct Move 
{
	Pos old;
	Pos new;
}

Best_Move Min_Iteration (ChessBoard board, int depth, Move move);

Best_Move Max_Iteration (ChessBoard board, int depth, Move move);


class MiniMax
{
public:
    // std::vector<Particle> particles;
    // std::vector<Particle> newParticles;
    // std::unique_ptr<INBodySimulator> nbodySimulator;

    // List of variables that need to be global across class (if any)

    Move Generate_Next(ChessBoard board, int depth);

    void print_move(Move move);
};

#endif
