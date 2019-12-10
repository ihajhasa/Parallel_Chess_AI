#include "gen_moves.h"
		// Remove the unnecessary ones later //

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

Move create_move(int oldrow, int oldcol, int newrow, int newcol)
{
	Pos *Old = new Pos;
	Pos *New = new Pos;
	Old -> row = oldrow;
	Old -> col = oldcol;
	New -> row = newrow;
	New -> col = newcol;

	Move move;
	move.Old = *Old;
	move.New = *New;

	delete Old;
	delete New;

	return move;
}

int is_valid_pos(int row, int col)
{
	return (0 <= row && row < 8 && 0 <= col && col < 8) ? 1 : 0;
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

std::vector<Move> gen_all_next_moves_parallel(ChessBoard B, int color)
{
	int idx, row, col;
	Piece *p;
	std::vector<Move> moves;
	std::vector<std::vector<Move>> submoves;
	submoves.resize(64);

	#pragma omp for schedule(dynamic)
	for(idx = 0; idx < 64; idx++)
	{
		row = idx/8;
		col = idx%8;
		p = B.lookup(row, col);
		if(p != NULL && p->color == color)
		{
			submoves[idx] = gen_next_moves(B, row, col);
		}
	}

	#pragma omp for schedule(dynamic)
	for(idx = 0; idx < 64; idx++)
	{
		#pragma omp critical
		moves.insert(std::end(moves), std::begin(submoves[idx]), std::end(submoves[idx]));

	}

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

float evaluate_quick_helper(int player_count[6], int opponent_count[6])
{
	// Computing the Evaluated Score
 	float Score = 0.f;

 	Score += 200.f * (float)((float)player_count[KING] - (float)opponent_count[KING]);
 	Score += 9.f * (float)((float)player_count[QUEEN] - (float)opponent_count[QUEEN]);
 	Score += 5.f * (float)((float)player_count[ROOK] - (float)opponent_count[ROOK]);
 	Score += 3.f * (float)((float)player_count[BISHOP] - (float)opponent_count[BISHOP]);
 	Score += 3.f * (float)((float)player_count[KNIGHT] - (float)opponent_count[KNIGHT]);
 	Score += 1.f * (float)((float)player_count[PAWN] - (float)opponent_count[PAWN]);

 	return Score;
}

float evaluate_quick(ChessBoard board, int color)
{
	int white_count[6], black_count[6];
	int idx, row, col;
	Piece *p;

	for(idx = PAWN; idx < KING; idx++)
	{
		white_count[idx] = 0;
		black_count[idx] = 0;
	}

	for(idx = 0; idx < 64; idx++)
	{
		row = idx/8;
		col = idx%8;

		p = board.lookup(row, col);
		if(p != NULL && p->color == BLACK)
			black_count[p->name] += 1;
		if(p != NULL && p->color == WHITE)
			white_count[p->name] += 1;
	}

	if(color == WHITE)
		return evaluate_quick_helper(white_count, black_count);
	if(color == BLACK)
		return evaluate_quick_helper(black_count, white_count);

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