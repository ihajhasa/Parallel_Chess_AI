#include "board_rep.h"
#include "minimax.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>			// Remove the unnecessary ones later //
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

// Minimax associates white as max player: 1
//     and associates black as min player: 0

// Set the precedence that the Evaluate function returns a float between 0.0 and 10.0.

#define MAX 1
#define MIN 0

Best_Move Min_Iteration (ChessBoard board, int depth, Move move);

class Best_Move
{
public:
	Move move;
	float score;

	static inline Best_Move Compare_Max (const Best_Move & old, 
										 const Best_Move & new)
	{
		if (new >= old) return new;
		return old;
	}

	static inline Best_Move Compare_Min (const Best_Move & old, 
										 const Best_Move & new)
	{
		if (new <= old) return new;
		return old;
	}
};

Best_Move Max_Iteration (ChessBoard board, int depth, Move move)
{
	if (!depth)
		{
		   Best_Move Last;
		   Last.score = MiniMax::Evaluate (board, MAX);
		   Last.move = move;
		   board::free_board();
		   return Last;
		}
	else
	{
		// Copy Board here and call it board_c
		ChessBoard board_c = *(board::copy());
		Best_Move Max;
		Max.score = 0.f;
		vector<Move> Moves = All_Next_Moves(board_c, MAX);
		for (vector<Move>::iterator it = Moves.begin();
			 it != Moves.end(); ++it)
		{
			Move Curr_Move = *it;
			Pos old, new;
			old = Curr_Move.old;
			new = Curr_Move.new;
			board_c::move(old.row, old.col, new.row, new.col);
			Best_Move New = Min_Iteration(board_c, depth - 1, Curr_Move);
			Max = Max::Compare_Max(Max, New);
		}

		board_c::free_board();
		return Max;
	}
}

Best_Move Min_Iteration (ChessBoard board, int depth, Move move)
{
	if (!depth)
	{
		Best_Move Last;
	    Last.score = MiniMax::Evaluate (board, MIN);
	    Last.move = move;
	    board::free_board();
	    return Last;
	}
	else
	{	
		ChessBoard board_c = *(board::copy());
		Best_Move Min;
		Min.score = 10.f;
		vector<Move> Moves = All_Next_Moves(board_c, MIN);
		for (vector<Move>::iterator it = Moves.begin();
			 it != Moves.end(); ++it)
		{
			Move Curr_Move = *it;
			Pos old, new;
			old = Curr_Move.old;
			new = Curr_Move.new;
			board_c::move(old.row, old.col, new.row, new.col);
			Best_Move New = Max_Iteration(board_c, depth - 1, Curr_Move);
			Min = Min::Compare_Min(Min, New);
		}
		board_c::free_board();
		return Min;
	}
}

float scale (float score)
{
	float ubound = 10.f;
	float lbound = 0.f;

	if (score < 0.f) return 0.f;

	score = score/8.f;

	if (score > 10.f) score = 10.f;

	return score;
}


float MiniMax::Evaluate(ChessBoard board, int player)
{

	int *Player_Pieces = new int[2][7];
	int player2 = (player + 1) % 2;
	vector<Move> MaxMoves, MinMoves;


	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			Player_Pieces[i][j] = 0;
		}
	}

	if (player == MAX)
	{
		MaxMoves = MiniMax::All_Next_Moves(board, player);
		MinMoves = MiniMax::All_Next_Moves(board, player2);
	}

	else
	{
		MaxMoves = MiniMax::All_Next_Moves(board, player2);
		MinMoves = MiniMax::All_Next_Moves(board, player);
	}
	// Mobility of Player 1

	Player_Pieces[MAX][6] = MaxMoves.length();
	Player_Pieces[MIN][6] = MinMoves.length();

	for(int row = 0; row < 8; row++)
	{
		for(int col = 0; col < 8; col++)
		{
			Piece *Curr_P = board::lookup(row, col);

			if (Curr_P == NULL) continue;
			Player_Pieces[Piece_getcolor(*Curr_P) - 6][Piece_getname(*Curr_P)] ++;
		}
	}
 	
 	// Computing the Evaluated Score
 	float Score = 0.f;

 	Score += 200.f * <float>(Player_Pieces[player][KING] - Player_Pieces[player2][KING]);
 	Score += 9.f * <float>(Player_Pieces[player][QUEEN] - Player_Pieces[player2][QUEEN]);
 	Score += 5.f * <float>(Player_Pieces[player][ROOK] - Player_Pieces[player2][ROOK]);
 	Score += 3.f * <float>(Player_Pieces[player][BISHOP] - Player_Pieces[player2][BISHOP]);
 	Score += 3.f * <float>(Player_Pieces[player][KNIGHT] - Player_Pieces[player2][KNIGHT]);
 	Score += 1.f * <float>(Player_Pieces[player][PAWN] - Player_Pieces[player2][PAWN]);
 	Score += 0.1f * <float>(Player_Pieces[player][7] - Player_Pieces[player2][7]);
 	return scale(Score);
}

Move create_Move(int or, int oc, int nr, int nc)
{
	Pos old, new;
	old.row = or;
	old.col = oc;
	new.row = nr;
	new.col = nc;

	Move move;
	move.old = old;
	move.new = new;
	return move;
}

vector<Move> MiniMax::All_Next_Moves(ChessBoard board, int player)
{

	vector<Move> All_Moves;
}

Move MiniMax::Generate_Next(ChessBoard board, int depth)
{

	if (board::get_board_color() == WHITE) return Max_Iteration(board, depth, create_Move(0, 0, 0, 0));
	return Min_Iteration(board, depth, create_Move(0, 0, 0, 0));
}
