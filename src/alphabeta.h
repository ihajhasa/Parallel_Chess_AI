#ifndef ALPHABETA_H
#define ALPHABETA_H

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
};

struct Move 
{
	Pos Old;
	Pos New;
};

struct Best_Move
{
    Move move;
    float score;
};


class AlphaBeta
{
public:
    // std::vector<Particle> particles;
    // std::vector<Particle> newParticles;
    // std::unique_ptr<INBodySimulator> nbodySimulator;

    // List of variables that need to be global across class (if any)

    Move Generate_Next(ChessBoard board, int depth);

    void print_move(ChessBoard board, Move move);
};

#endif
