#include "minimax.h"

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

int is_valid_pos(int row, int col)
{
	if(row < 0 || row >= 8 || col < 0 || col >= 8) return 0;
	return 1;
	// return (0 <= row && row < 8 && 0 <= col && col < 8) ? 1 : 0;
}

Move create_move(int oldrow, int oldcol, int newrow, int newcol)
{
	Move mv;
	mv.oldrow = oldrow;
	mv.oldcol = oldcol;
	mv.newrow = newrow;
	mv.newcol = newcol;
	return mv;
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
				std::cout << std::endl;
				std::vector<Move> submoves = gen_next_moves(B, row, col);
				moves.insert(std::end(moves), std::begin(submoves), std::end(submoves));
			}
		}
	}

	return moves;
}