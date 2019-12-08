#include "board.h"
#include "minimax.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>			// Remove the unnecessary ones later //
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>


// Set the precedence that the Evaluate function returns a float between 0.0 and 10.0.

class Best_Move
{
public:
	Move move;
	float score;

	static inline Best_Move Compare_Max (const Best_Move & old, 
										 const Best_Move & new)
	{
		if (new > old) return new;
		return old;
	}

	static inline Best_Move Compare_Min (const Best_Move & old, 
										 const Best_Move & new)
	{
		if (new < old) return new;
		return old;
	}
};

Best_Move Max_Iteration (ChessBoard board, int depth, Move move)
{
	if (!depth)
		{
		   Best_Move Last;
		   Last.score = MiniMax::Evaluate (board, 1);
		   Last.move = move;
		   return Last;
		}
	else
	{
		// Copy Board here and call it board_c
		Best_Move Max;
		Max.score = 0.f;
		vector<Move> Moves = All_Next_Moves(board_c, 1);
		for (vector<Move>::iterator it = Moves.begin();
			 it != Moves.end(); ++it)
		{
			Move Curr_Move = *it;
			Pos old, new;
			old = Curr_Move.old;
			new = Curr_Move.new;
			board_c::move(old.row, old.col, new.row, new.col);
			Optimal_Move New = Min_Iteration(board_c, depth - 1);
			Max = Max::Compare_Max(Max, New);
		}

		return Max;
	}
}

Best_Move Min_Iteration (ChessBoard board, int depth, Move move)
{
	if (!depth)
	{
		Best_Move Last;
	    Last.score = MiniMax::Evaluate (board, 1);
	    Last.move = move;
	    return Last;
	}
	else
	{
		Best_Move Min = 10.f;
		vector<Move> Moves = All_Next_Moves(board, 1);
		for (vector<Move>::iterator it = Moves.begin();
			 it != Moves.end(); ++it)
		{
			Move Curr_Move = *it;
			Pos old, new;
			old = Curr_Move.old;
			new = Curr_Move.new;
			board_c::move(old.row, old.col, new.row, new.col);
			Optimal_Move New = Max_Iteration(board_c, depth - 1);
			Min = Min::Compare_Min(Min, New);
		}

		return Min;
	}
}


MiniMax::Evaluate(ChessBoard board, int player)
{

}

MiniMax::All_Next_Moves(ChessBoard board, int player)
{

}

MiniMax::Generate_Next(ChessBoard board, int depth)
{

}
