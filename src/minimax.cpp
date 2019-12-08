#include "board_rep.h"
#include "minimax.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>			// Remove the unnecessary ones later //
#include <stdio.h>
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

void find_piece(ChessBoard CB, Pos position)
{
	int name = CB::lookup(position.row, position.col)
	switch (name)
	{
		case PAWN:
			cout << "PAWN";
			break;
		case KING:
			cout << "KING";
			break;
		case QUEEN:
			cout << "QUEEN";
			break;
		case KNIGHT:
			cout << "KNIGHT";
			break;
		case ROOK:
			cout << "ROOK";
			break;
		case BISHOP:
			cout << "BISHOP";
			break;
		default:
			cout << "EMPTY";
			break;
	}
	return;
}

void MiniMax::print_move(ChessBoard CB, Move move)
{
	cout << "Moving Piece: ";
	find_piece(CB, move.old);
	cout << endl;
	cout << "(" << to_string(move.old.row) << ", " << to_string(move.old.col) << ")";
	cout << " to ";
	cout << "(" << to_string(move.new.row) << ", " << to_string(move.new.col) << ")";
	cout << endl;
	return;
}

Best_Move Max_Iteration (ChessBoard board, int depth, Move move)
{
	if (!depth)
		{
		   Best_Move Last;
		   Last.score = MiniMax::Evaluate (board, board::get_board_color());
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
		vector<Move> Moves = All_Next_Moves(board_c, board::get_board_color());
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

int get_opponent_color(int AI)
{
	return (AI == BLACK) ? WHITE : BLACK;
}

Best_Move Min_Iteration (ChessBoard board, int depth, Move move)
{
	if (!depth)
	{
		Best_Move Last;
		int AI_color = board::get_board_color();
	    Last.score = MiniMax::Evaluate (board, get_opponent_color(AI_color));
	    Last.move = move;
	    board::free_board();
	    return Last;
	}
	else
	{	
		ChessBoard board_c = *(board::copy());
		Best_Move Min;
		Min.score = 10.f;
		vector<Move> Moves = All_Next_Moves(board_c, get_opponent_color(AI_color));
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


float MiniMax::Evaluate(ChessBoard board, int color)
{

	int *Player_Pieces = new int[2][7];
	int player = color -  6;
	int player2 = (player + 1) % 2;
	vector<Move> P1Moves, P2Moves;


	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			Player_Pieces[i][j] = 0;
		}
	}


	P1Moves = MiniMax::All_Next_Moves(board, player);
	P2Moves = MiniMax::All_Next_Moves(board, player2);

	// Mobility of Player 1

	Player_Pieces[player][6] = P1Moves.length();
	Player_Pieces[player2][6] = P2Moves.length();

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

Move create_move(int or, int oc, int nr, int nc)
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


std::vector<Move> gen_next_moves_pawn(ChessBoard B, int row, int col)
{
	std::vector<Move> moves;
	int newrow, newcol;
	Piece *tmp, *p;

	p = B.lookup(row, col);

	if(p == NULL) return moves; // empty square
	if(p->name != PAWN) return moves; // wrong piece

	if(p->color == BLACK)
	{
		// go down
		if(row == 1)
		{
			// can move 1 or 2
			newrow = row + 1;
			tmp = B.lookup(newrow, col);
			if(tmp == NULL)
			{
				moves.push_back(create_move(row, col, newrow, col));
				newrow = row + 2;
				tmp = B.lookup(newrow, col);
				if(tmp == NULL)
					moves.push_back(create_move(row, col, newrow, col));
			}
			
		}
		else
		{
			// move 1 down
			newrow = row + 1;
			tmp = B.lookup(newrow, col);
			if(tmp == NULL)
				moves.push_back(create_move(row, col, newrow, col));
		}

		// go diagonal left
		newrow = row + 1; 
		newcol = col - 1;
		tmp = B.lookup(newrow, newcol);
		if(tmp != NULL && tmp->color != p->color)
			moves.push_back(create_move(row, col, newrow, newcol));

		// go diagonal right
		newrow = row + 1; 
		newcol = col + 1;
		tmp = B.lookup(newrow, newcol);
		if(tmp != NULL && tmp->color != p->color)
			moves.push_back(create_move(row, col, newrow, newcol));

	}
	else if(p->color == WHITE)
	{
		// go up
		if(row == 6)
		{
			// can move 1 or 2
			newrow = row - 1;
			tmp = B.lookup(newrow, col);
			if(tmp == NULL)
			{
				moves.push_back(create_move(row, col, newrow, col));
				newrow = row - 2;
				tmp = B.lookup(newrow, col);
				if(tmp == NULL)
					moves.push_back(create_move(row, col, newrow, col));
			}
			
		}
		else
		{
			// move 1 up
			newrow = row - 1;
			tmp = B.lookup(newrow, col);
			if(tmp == NULL)
				moves.push_back(create_move(row, col, newrow, col));
		}

		// go diagonal left
		newrow = row - 1; 
		newcol = col - 1;
		tmp = B.lookup(newrow, newcol);
		if(tmp != NULL && tmp->color != p->color)
			moves.push_back(create_move(row, col, newrow, newcol));

		// go diagonal right
		newrow = row - 1; 
		newcol = col + 1;
		tmp = B.lookup(newrow, newcol);
		if(tmp != NULL && tmp->color != p->color)
			moves.push_back(create_move(row, col, newrow, newcol));
	}


	return moves;
}

std::vector<Move> gen_next_moves_rook(ChessBoard B, int row, int col)
{
	std::vector<Move> moves;
	int newrow, newcol;
	Piece *tmp, *p;

	p = B.lookup(row, col);

	if(p == NULL) return moves; // empty spot

	// will use this function to generate moves for queen 
	// unsafe practice might remove if errors arise
	// if(p->name != ROOK) return moves; // wrong piece

	//	sweep up board
	for(newrow = row - 1; newrow >= 0; newrow--)
	{
		tmp = B.lookup(newrow, col);
		if(tmp == NULL)
			moves.push_back(create_move(row, col, newrow, col));
		else if(tmp != NULL)
		{
			if(tmp->color != p->color) moves.push_back(create_move(row, col, newrow, col));
			newrow = -1;
		}
	}

	// sweep down board
	for(newrow = row + 1; newrow < 8; newrow++)
	{
		tmp = B.lookup(newrow, col);
		if(tmp == NULL)
			moves.push_back(create_move(row, col, newrow, col));
		else if(tmp != NULL)
		{
			if(tmp->color != p->color) moves.push_back(create_move(row, col, newrow, col));
			newrow = 8;
		}
	}

	// sweep left board
	for(newcol = col - 1; newcol >= 0; newcol--)
	{
		tmp = B.lookup(row, newcol);
		if(tmp == NULL)
			moves.push_back(create_move(row, col, row, newcol));
		else if(tmp != NULL)
		{
			if(tmp->color != p->color) moves.push_back(create_move(row, col, row, newcol));
			newcol = -1;
		}
	}

	// sweep right board
	for(newcol = col + 1; newcol < 8; newcol++)
	{
		tmp = B.lookup(row, newcol);
		if(tmp == NULL)
			moves.push_back(create_move(row, col, row, newcol));
		else if(tmp != NULL)
		{
			if(tmp->color != p->color) moves.push_back(create_move(row, col, row, newcol));
			newcol = 8;
		}
	}

	return moves;
}

std::vector<Move> gen_next_moves_knight(ChessBoard B, int row, int col)
{
	std::vector<Move> moves;
	int newrow, newcol;
	Piece *tmp, *p;

	p = B.lookup(row, col);

	if(p == NULL) return moves; // empty square
	if(p->name != KNIGHT) return moves; // wrong piece

	// U 2 L 1
	newrow = row - 2;
	newcol = col - 1;
	if(is_valid_pos(newrow, newcol))
	{
		tmp = B.lookup(newrow, newcol);
		if(tmp == NULL) 
			moves.push_back(create_move(row, col, newrow, newcol));
		else if(tmp != NULL && tmp->color != p->color) 
			moves.push_back(create_move(row, col, newrow, newcol));
	}

	// U 2 R 1
	newrow = row - 2;
	newcol = col + 1;
	if(is_valid_pos(newrow, newcol))
	{
		tmp = B.lookup(newrow, newcol);
		if(tmp == NULL) 
			moves.push_back(create_move(row, col, newrow, newcol));
		else if(tmp != NULL && tmp->color != p->color) 
			moves.push_back(create_move(row, col, newrow, newcol));
	}

	// U 1 L 2
	newrow = row - 1;
	newcol = col - 2;
	if(is_valid_pos(newrow, newcol))
	{
		tmp = B.lookup(newrow, newcol);
		if(tmp == NULL) 
			moves.push_back(create_move(row, col, newrow, newcol));
		else if(tmp != NULL && tmp->color != p->color) 
			moves.push_back(create_move(row, col, newrow, newcol));
	}

	// U 1 R 2
	newrow = row - 1;
	newcol = col + 2;
	if(is_valid_pos(newrow, newcol))
	{
		tmp = B.lookup(newrow, newcol);
		if(tmp == NULL) 
			moves.push_back(create_move(row, col, newrow, newcol));
		else if(tmp != NULL && tmp->color != p->color) 
			moves.push_back(create_move(row, col, newrow, newcol));
	}

	// D 1 L 2
	newrow = row + 1;
	newcol = col - 2;
	if(is_valid_pos(newrow, newcol))
	{
		tmp = B.lookup(newrow, newcol);
		if(tmp == NULL) 
			moves.push_back(create_move(row, col, newrow, newcol));
		else if(tmp != NULL && tmp->color != p->color) 
			moves.push_back(create_move(row, col, newrow, newcol));
	}

	// D 1 R 2
	newrow = row + 1;
	newcol = col + 2;
	if(is_valid_pos(newrow, newcol))
	{
		tmp = B.lookup(newrow, newcol);
		if(tmp == NULL) 
			moves.push_back(create_move(row, col, newrow, newcol));
		else if(tmp != NULL && tmp->color != p->color) 
			moves.push_back(create_move(row, col, newrow, newcol));
	}

	// D 2 L 1
	newrow = row + 2;
	newcol = col - 1;
	if(is_valid_pos(newrow, newcol))
	{
		tmp = B.lookup(newrow, newcol);
		if(tmp == NULL) 
			moves.push_back(create_move(row, col, newrow, newcol));
		else if(tmp != NULL && tmp->color != p->color) 
			moves.push_back(create_move(row, col, newrow, newcol));
	}

	// D 2 R 1
	newrow = row + 2;
	newcol = col + 1;
	if(is_valid_pos(newrow, newcol))
	{
		tmp = B.lookup(newrow, newcol);
		if(tmp == NULL) 
			moves.push_back(create_move(row, col, newrow, newcol));
		else if(tmp != NULL && tmp->color != p->color) 
			moves.push_back(create_move(row, col, newrow, newcol));
	}

	return moves;
}

std::vector<Move> gen_next_moves_bishop(ChessBoard B, int row, int col)
{
	std::vector<Move> moves;
	int newrow, newcol;
	Piece *tmp, *p;

	p = B.lookup(row, col);

	if(p == NULL) return moves;

	// will use this function to generate moves for queen 
	// unsafe practice might remove if errors arise
	// if(p->name != BISHOP) return moves; // wrong piece

	// sweep top left
	newrow = row - 1;
	newcol = col - 1;

	while(is_valid_pos(newrow, newcol))
	{
		tmp = B.lookup(newrow, newcol);
		if(tmp == NULL) moves.push_back(create_move(row, col, newrow, newcol));
		else if(tmp != NULL)
		{
			if(tmp->color != p->color) moves.push_back(create_move(row, col, newrow, newcol));
			newrow = -1;
			newcol = -1;
		}
		newrow--; newcol--;
	}

	// sweep top right
	newrow = row - 1;
	newcol = col + 1;

	while(is_valid_pos(newrow, newcol))
	{
		tmp = B.lookup(newrow, newcol);
		if(tmp == NULL) moves.push_back(create_move(row, col, newrow, newcol));
		else if(tmp != NULL)
		{
			if(tmp->color != p->color) moves.push_back(create_move(row, col, newrow, newcol));
			newrow = -1;
			newcol = -1;
		}

		newrow--; newcol++;
	}

	// sweep bottom left
	newrow = row + 1;
	newcol = col - 1;

	while(is_valid_pos(newrow, newcol))
	{
		tmp = B.lookup(newrow, newcol);
		if(tmp == NULL) moves.push_back(create_move(row, col, newrow, newcol));
		else if(tmp != NULL)
		{
			if(tmp->color != p->color) moves.push_back(create_move(row, col, newrow, newcol));
			newrow = -1;
			newcol = -1;
		}

		newrow++; newcol--;
	}

	// sweep bottom right
	newrow = row + 1;
	newcol = col + 1;

	while(is_valid_pos(newrow, newcol))
	{
		tmp = B.lookup(newrow, newcol);
		if(tmp == NULL) moves.push_back(create_move(row, col, newrow, newcol));
		else if(tmp != NULL)
		{
			if(tmp->color != p->color) moves.push_back(create_move(row, col, newrow, newcol));
			newrow = -1;
			newcol = -1;
		}

		newrow++; newcol++;
	}

	return moves;
}

std::vector<Move> gen_next_moves_queen(ChessBoard B, int row, int col)
{
	std::vector<Move> moves, m1, m2;

	if(B.lookup(row, col) == NULL || B.lookup(row, col)->name != QUEEN) return moves; // wrong piece

	m1 = gen_next_moves_rook(B, row, col);
	m2 = gen_next_moves_bishop(B, row, col);
	moves.insert(std::end(moves), std::begin(m1), std::end(m1));
	moves.insert(std::end(moves), std::begin(m2), std::end(m2));

	return moves;
}

std::vector<Move> gen_next_moves_king(ChessBoard B, int row, int col)
{
	std::vector<Move> moves;
	int newrow, newcol;
	Piece *tmp, *p;

	p = B.lookup(row, col);

	if(p == NULL) return moves; // empty square
	if(p->name != KING) return moves; // wrong piece

	for(newrow = row - 1; newrow < row + 1; newrow++)
	{
		for(newcol = col - 1; newcol < col + 1; newcol++)
		{
			tmp = B.lookup(newrow, newcol);

			if(tmp == NULL)
				moves.push_back(create_move(row, col, newrow, newcol));
			else if(tmp != NULL)
			{
				if(tmp->color != p->color) moves.push_back(create_move(row, col, newrow, newcol));
			}
		}
	}

	return moves;
}

std::vector<Move> gen_next_moves(ChessBoard B, int row, int col)
{
	std::vector<Move> moves;

	Piece p;
	Piece *pp;

	pp = B.lookup(row, col);

	if(pp == NULL) return moves; // that position is empty

	p = *pp;

	if(p.name == PAWN) return gen_next_moves_pawn(B, row, col);
	else if(p.name == ROOK) return gen_next_moves_rook(B, row, col);
	else if(p.name == KNIGHT) return gen_next_moves_knight(B, row, col);
	else if(p.name == BISHOP) return gen_next_moves_bishop(B, row, col);
	else if(p.name == QUEEN) return gen_next_moves_queen(B, row, col);
	else if(p.name == KING) return gen_next_moves_king(B, row, col);

	return moves;
}

std::vector<Move> gen_all_next_moves(ChessBoard B, int color)
{
	std::vector<Move> moves;
	int row, col;
	Piece *p;

	for(row = 0; row < 8; row++)
	{
		for(col = 0; col < 8; col++)
		{
			p = B.lookup(row, col);

			if(p != NULL && p->color == color)
			{
				std::vector<Move> submoves = gen_next_moves(B, row, col);
				moves.insert(std::end(moves), std::begin(submoves), std::end(submoves));
			}
		}
	}

	return moves;
}


vector<Move> MiniMax::All_Next_Moves(ChessBoard board, int color)
{

	return gen_all_next_moves(board, color);
}

Move MiniMax::Generate_Next(ChessBoard board, int depth)
{
	Max_Iteration(board, depth, create_move(0, 0, 0, 0));
}
