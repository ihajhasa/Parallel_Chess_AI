#include "board_rep.h"
#include "minimax.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>			// Remove the unnecessary ones later //


// Minimax associates white as max player: 1
//     and associates black as min player: 0

// Set the precedence that the Evaluate function returns a float between 0.0 and 10.0.

#define MAX 1
#define MIN 0


Move create_move(int oldrow, int oldcol, int newrow, int newcol)
{
	Pos *Old = new Pos;
	Pos *New = new Pos;
	Old -> row = oldrow;
	Old -> col = oldcol;
	New -> row = newrow;
	New -> col = newcol;

	Move *move = new Move;
	move -> Old = *Old;
	move -> New = *New;
	return *move;
}

int is_valid_pos(int row, int col)
{
	return (0 <= row && row < 8 && 0 <= col && col < 8) ? 1 : 0;
}

int is_valid_move(ChessBoard CB, Move move)
{
	if (CB.lookup(move.Old.row, move.Old.col) == NULL) return 1;
	else return 0;
}

void find_piece(ChessBoard CB, Pos position)
{
	Piece *type = CB.lookup(position.row, position.col);
	if (type == NULL) return;

	switch (type -> name)
	{
		case PAWN:
			std::cout << "PAWN";
			break;
		case KING:
			std::cout << "KING";
			break;
		case QUEEN:
			std::cout << "QUEEN";
			break;
		case KNIGHT:
			std::cout << "KNIGHT";
			break;
		case ROOK:
			std::cout << "ROOK";
			break;
		case BISHOP:
			std::cout << "BISHOP";
			break;
		default:
			std::cout << "EMPTY";
			break;
	}
	return;
}

void MiniMax::print_move(ChessBoard board, Move move)
{
	std::cout << "Moving Piece: ";
	find_piece(board, move.Old);
	std::cout << "\n";
	std::cout << "(" << std::to_string(move.Old.row) << ", " << std::to_string(move.Old.col) << ")";
	std::cout << " to ";
	std::cout << "(" << std::to_string(move.New.row) << ", " << std::to_string(move.New.col) << ")";
	std::cout << "\n";
	return;
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
			newrow = -5;
			newcol = -5;
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
			newrow = -5;
			newcol = -5;
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
			newrow = -5;
			newcol = -5;
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
			newrow = -5;
			newcol = -5;
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
			if(is_valid_pos(newrow, newcol))
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


std::vector<Move> All_Next_Moves(ChessBoard board, int color)
{

	return gen_all_next_moves(board, color);
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


float evaluate(ChessBoard board, int color)
{

	int Player_Pieces[2][7];
	int player = color -  6;
	int player2 = (player + 1) % 2;
	std::vector<Move> P1Moves, P2Moves;


	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			Player_Pieces[i][j] = 0;
		}
	}


	P1Moves = All_Next_Moves(board, player);
	P2Moves = All_Next_Moves(board, player2);

	// Mobility of Player 1

	Player_Pieces[player][6] = P1Moves.size();
	Player_Pieces[player2][6] = P2Moves.size();

	for(int row = 0; row < 8; row++)
	{
		for(int col = 0; col < 8; col++)
		{
			Piece *Curr_P = board.lookup(row, col);

			if (Curr_P == NULL) continue;
			Player_Pieces[Piece_getcolor(*Curr_P) - 6][Piece_getname(*Curr_P)] ++;
		}
	}
 	
 	// Computing the Evaluated Score
 	float Score = 0.f;

 	Score += 200.f * ((float)(Player_Pieces[player][KING] - Player_Pieces[player2][KING]));
 	Score += 9.f * ((float)(Player_Pieces[player][QUEEN] - Player_Pieces[player2][QUEEN]));
 	Score += 5.f * ((float)(Player_Pieces[player][ROOK] - Player_Pieces[player2][ROOK]));
 	Score += 3.f * ((float)(Player_Pieces[player][BISHOP] - Player_Pieces[player2][BISHOP]));
 	Score += 3.f * ((float)(Player_Pieces[player][KNIGHT] - Player_Pieces[player2][KNIGHT]));
 	Score += 1.f * ((float)(Player_Pieces[player][PAWN] - Player_Pieces[player2][PAWN]));
 	Score += 0.1f * ((float)(Player_Pieces[player][6] - Player_Pieces[player2][6]));
 	
 	return scale(Score);
}


Best_Move *Compare_Max (Best_Move *prev, 
									 Best_Move *curr, Move move)
{
	if (curr -> score >= prev -> score) 
	{
		// free(prev);
		curr -> move = move;
		return curr;
	}
	// free(curr);
	return prev;
}

Best_Move *Compare_Min (Best_Move *prev, 
									 Best_Move *curr, Move move)
{
	if (curr -> score <= prev -> score) 
	{
		// free(prev);
		curr -> move = move;
		return curr;
	}
	// free(curr);
	return prev;
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


Best_Move *Max_Iteration (ChessBoard board, int depth, Move move, int color)
{

	if (depth == 0)
	{
		Best_Move *Last = new Best_Move;
		Last -> score = evaluate (board, color);
		Last -> move = move;
		return Last;
	}

	else
	{
		Best_Move *Max = new Best_Move;
		Max -> score = 0.f;

		std::vector<Move> Moves = All_Next_Moves(board, color);

		for (std::vector<Move>::iterator it = Moves.begin();
			 it != Moves.end(); ++it)
		{
			// Copy Board here and call it board_c
			ChessBoard board_c = *(board.copy());
			Move Curr_Move = *it;

			if (!is_valid_move(board, Curr_Move)) continue;
			board_c.move(Curr_Move.Old.row, Curr_Move.Old.col, Curr_Move.New.row, Curr_Move.New.col);

			Best_Move *New_Move = Min_Iteration(board_c, depth - 1, Curr_Move, get_opponent_color(color));
			
			Max = Compare_Max(Max, New_Move, Curr_Move);
			
		}

		return Max;
	}
}


Best_Move *Min_Iteration (ChessBoard board, int depth, Move move, int color)
{
	if (depth == 0)
	{
		Best_Move *Last = new Best_Move;
		Last -> score = evaluate (board, color);
		return Last;
	}

	else
	{	
		Best_Move *Min = new Best_Move;
		Min -> score = 10.f;

		std::vector<Move> Moves = All_Next_Moves(board, color);
		for (std::vector<Move>::iterator it = Moves.begin();
			 it != Moves.end(); ++it)
		{
			// Copy Board here and call it board_c
			ChessBoard board_c = *(board.copy());
			Move Curr_Move = *it;

			if (!is_valid_move(board, Curr_Move)) continue;
			board_c.move(Curr_Move.Old.row, Curr_Move.Old.col, Curr_Move.New.row, Curr_Move.New.col);
			Best_Move *New_Move = Max_Iteration(board_c, depth - 1, Curr_Move, get_opponent_color(color));
			Min = Compare_Min(Min, New_Move, Curr_Move);
		}

		return Min;
	}
}



Move MiniMax::Generate_Next(ChessBoard board, int depth, int color)
{
	Best_Move *Optimal = Max_Iteration(board, depth, create_move(0, 0, 0, 0), color);
	return Optimal -> move;
}
