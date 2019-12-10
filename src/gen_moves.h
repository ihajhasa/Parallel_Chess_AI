#ifndef GEN_MOVES
#define GEN_MOVES

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <iterator>
#include <cstring>	
#include "board_rep.h"

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

void find_piece(ChessBoard CB, Pos position);
int is_valid_pos(int row, int col);
Move create_move(int oldrow, int oldcol, int newrow, int newcol);
std::vector<Move> gen_next_moves_pawn(ChessBoard B, int row, int col);
std::vector<Move> gen_next_moves_rook(ChessBoard B, int row, int col);
std::vector<Move> gen_next_moves_knight(ChessBoard B, int row, int col);
std::vector<Move> gen_next_moves_bishop(ChessBoard B, int row, int col);
std::vector<Move> gen_next_moves_queen(ChessBoard B, int row, int col);
std::vector<Move> gen_next_moves_king(ChessBoard B, int row, int col);
std::vector<Move> gen_next_moves(ChessBoard B, int row, int col);
std::vector<Move> gen_all_next_moves_parallel(ChessBoard B, int color);
std::vector<Move> gen_all_next_moves(ChessBoard B, int color);
std::vector<Move> All_Next_Moves(ChessBoard board, int color);
float scale (float score);
float evaluate(ChessBoard board, int color);
float evaluate_quick(ChessBoard board, int color);


#endif