#include "minimax.h"
		// Remove the unnecessary ones later //


// Minimax associates white as max player: 1
//     and associates black as min player: 0

// Set the precedence that the Evaluate function returns a float between 0.0 and 10.0.

#define MAX 1
#define MIN 0


// void MiniMax::print_move(ChessBoard board, Move move)
// {
// 	std::cout << "Moving Piece: ";
// 	find_piece(board, move.Old);
// 	std::cout << "\n";
// 	std::cout << "(" << std::to_string(move.Old.row) << ", " << std::to_string(move.Old.col) << ")";
// 	std::cout << " to ";
// 	std::cout << "(" << std::to_string(move.New.row) << ", " << std::to_string(move.New.col) << ")";
// 	std::cout << "\n";
// 	return;
// }


Best_Move Compare_Max (Best_Move prev, 
									 Best_Move curr, Move move)
{

	Best_Move rv;

	if (curr.score >= prev.score) 
	{
		// free(prev);
		rv.move = move;
		rv.score = curr.score;
		return rv;
	}
	// free(curr);
	rv.move = prev.move;
	rv.score = prev.score;

	return rv;
}

Best_Move Compare_Min (Best_Move prev, 
									 Best_Move curr, Move move)
{
	Best_Move rv;

	if (curr.score < prev.score) 
	{
		// free(prev);
		rv.move = move;
		rv.score = curr.score;
		return rv;
	}
	// free(curr);
	rv.move = prev.move;
	rv.score = prev.score;

	return rv;
}

void intStr(int color)
{
	if (color == BLACK) std::cout << "BLACK\n";
	else std::cout << "WHITE\n";
}


void Print_piece(Piece *p_p)
{
	if(p_p == NULL) 
	{
		std::cout << "Emp";
		return;
	}


	Piece p = *p_p;

	if (p.color == BLACK)
		std::cout << "B";
	else if (p.color == WHITE)
		std::cout << "W";

	if (p.name == PAWN)
		std::cout << "Pa";
	else if (p.name == ROOK)
		std::cout << "Ro";
	else if (p.name == KNIGHT)
		std::cout << "Kn";
	else if (p.name == BISHOP)
		std::cout << "Bi";
	else if (p.name == QUEEN)
		std::cout << "Qu";
	else if (p.name == KING)
		std::cout << "Ki";
}

void Print_board(ChessBoard B)
{
	std::cout << "-----------------------------------------" << std::endl;
	for(int row = 0; row < 8; row++)
	{
		for(int col = 0; col < 8; col++)
		{
			std::cout << "| ";
			Print_piece(B.lookup(row, col));
		}
		std::cout << "|" << std::endl;
		std::cout << "-----------------------------------------" << std::endl;
	}
	std::cout << std::endl << std::endl;
}


int get_opponent_color(int AI)
{
	return (AI == BLACK) ? WHITE : BLACK;
}


Best_Move Max_Iteration (ChessBoard board, int depth, Move move, int color)
{

	if (depth == 0)
	{
		Best_Move Last;
		Last.score = evaluate(board, color);
		Last.move = move;
		return Last;
	}

	else
	{
		Best_Move Max;
		Max.score = (float)INT_MIN;

		std::vector<Move> Moves = All_Next_Moves(board, color);

		for (std::vector<Move>::iterator it = Moves.begin();
			 it != Moves.end(); ++it)
		{
			// Copy Board here and call it board_c
			ChessBoard *board_c = board.copy();
			Move Curr_Move = *it;

			board_c->move(Curr_Move.Old.row, Curr_Move.Old.col, Curr_Move.New.row, Curr_Move.New.col);

			Best_Move New_Move = Min_Iteration(*board_c, depth - 1, Curr_Move, get_opponent_color(color));
			
			Max = Compare_Max(Max, New_Move, Curr_Move);

			board_c->free_board();
			free(board_c);
		}

		return Max;
	}
}


Best_Move Min_Iteration (ChessBoard board, int depth, Move move, int color)
{
	if (depth == 0)
	{
		Best_Move Last;
		Last.move = move;
		Last.score = evaluate(board, color);
		return Last;
	}

	else
	{	
		Best_Move Min;
		Min.score = (float)INT_MAX;

		std::vector<Move> Moves = All_Next_Moves(board, color);
		for (std::vector<Move>::iterator it = Moves.begin();
			 it != Moves.end(); ++it)
		{
			// Copy Board here and call it board_c
			ChessBoard *board_c = board.copy();
			Move Curr_Move = *it;

			board_c->move(Curr_Move.Old.row, Curr_Move.Old.col, Curr_Move.New.row, Curr_Move.New.col);
			Best_Move New_Move = Max_Iteration(*board_c, depth - 1, Curr_Move, get_opponent_color(color));
			Min = Compare_Min(Min, New_Move, Curr_Move);

			board_c->free_board();
			free(board_c);
		}

		return Min;
	}
}



Move MiniMax::Generate_Next(ChessBoard board, int depth, int color)
{
	Move holder = create_move(0, 0, 0, 0);
	Best_Move Optimal = Max_Iteration(board, depth, holder, color);
	Move mv = Optimal.move;
	return mv;
}


