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
    Best_Move *next;
};

struct Top
{
    Best_Move *Head;
};

Best_Move *AlphaBetaMax (ChessBoard board, float alpha, float beta, int depth, Move old, int color)

Best_Move *AlphaBetaMin (ChessBoard board, float alpha, float beta, int depth, Move old, int color)


class AlphaBeta
{
public:
    // std::vector<Particle> particles;
    // std::vector<Particle> newParticles;
    // std::unique_ptr<INBodySimulator> nbodySimulator;

    // List of variables that need to be global across class (if any)

    Move Generate_Next(ChessBoard board, int depth, int color);

    void print_move(ChessBoard board, Move move);
};

#endif

#endif
