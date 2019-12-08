#ifndef MINIMAX_H
#define MINIMAX_H

#include <math.h>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <limits.h>
#include <vector>

class Pos
{
public:
	int row;
	int col;
};

class Move 
{
public:
	Pos old;
	Pos new;
};


class MiniMax
{
public:
    // std::vector<Particle> particles;
    // std::vector<Particle> newParticles;
    // std::unique_ptr<INBodySimulator> nbodySimulator;

    // List of variables that need to be global across class (if any)

    float Evaluate(ChessBoard board, int color);

    std::vector<Move> All_Next_Moves(ChessBoard board, int color);

    Move Generate_Next(ChessBoard board, int depth);

    void print_move(Move move);
};

#endif
