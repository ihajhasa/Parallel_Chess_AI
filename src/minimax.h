#ifndef MINIMAX_H
#define MINIMAX_H

#include <math.h>

class Pos
{
public:
	int row;
	int col;
	Pos() = default;
    Pos(int vrow, int vcol)
    {
        row = vrow;
        col = vcol;
    }	
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

    float Evaluate(ChessBoard board, int player);

    vector<Move> wAll_Next_Moves(ChessBoard board, int player);

    Move Generate_Next(ChessBoard board, int depth);


};

#endif
