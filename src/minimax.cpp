#include "minimax.h"

int is_occupied(ChessBoard B, int row, int col)
{
	if(B.lookup(row, col) == NULL) return 0;
	return 1;
}

int is_valid(int row, int col)
{
	if (0 <= row && row < 8 && 0 <= col && col < 8) return 1;
	else return 0;
}

int evaluate()
{
	return 0;
}

std::vector<ChessBoard> gen_all_next(ChessBoard B, int row, int col)
{
	std::vector<ChessBoard>NewBoards;
	Piece *pp, *tmpp, p;
	ChessBoard *newB;

	if(B.lookup(row, col) == NULL) return NewBoards;

	pp = B.lookup(row, col);
	p = *pp;

	if(p.name == PAWN) {return NewBoards;}
	if(p.name == ROOK) 
	{

		// all possible rook moves in the same column
		for(int newrow = row - 1; 0 <= newrow; newrow--)
		{
			tmpp = B.lookup(newrow, col);
			if(tmpp == NULL)
			{
				newB = B.copy();
				(*newB).move(row, col, newrow, col);
				NewBoards.push_back((*newB));
			}
			if(tmpp != NULL)
			{

				if(p.color != tmpp->color)
				{
					newB = B.copy();
					(*newB).move(row, col, newrow, col);
					NewBoards.push_back((*newB));
				}
				newrow = -1;
			}
		}
		for(int newrow = row + 1; newrow < 8; newrow++)
		{
			tmpp = B.lookup(newrow, col);
			if(tmpp == NULL)
			{
				newB = B.copy();
				(*newB).move(row, col, newrow, col);
				NewBoards.push_back((*newB));
			}
			if(tmpp != NULL)
			{

				if(p.color != tmpp->color)
				{
					newB = B.copy();
					(*newB).move(row, col, newrow, col);
					NewBoards.push_back((*newB));
				}
				newrow = 8;
			}
		}
		//-----------------------------------------------
		// all possible rook moves in the same row
		for(int newcol = col - 1; 0 <= newcol; newcol--)
		{
			tmpp = B.lookup(row, newcol);
			if(tmpp == NULL)
			{
				newB = B.copy();
				(*newB).move(row, col, row, newcol);
				NewBoards.push_back((*newB));
			}
			if(tmpp != NULL)
			{

				if(p.color != tmpp->color)
				{
					newB = B.copy();
					(*newB).move(row, col, row, newcol);
					NewBoards.push_back((*newB));
				}
				newcol = -1;
			}
		}
		for(int newcol = col + 1; newcol < 8; newcol++)
		{
			tmpp = B.lookup(row, newcol);
			if(tmpp == NULL)
			{
				newB = B.copy();
				(*newB).move(row, col, row, newcol);
				NewBoards.push_back((*newB));
			}
			if(tmpp != NULL)
			{

				if(p.color != tmpp->color)
				{
					newB = B.copy();
					(*newB).move(row, col, row, newcol);
					NewBoards.push_back((*newB));
				}
				newcol = 8;
			}
		}
		//-------------------------------------------------
	}
	if(p.name == KNIGHT) 
	{
		int newrow, newcol;


		// Up 2, Left 1
		newrow = row - 2;
		newcol = col - 1;
		if(is_valid(newrow, newcol) && (B.lookup(newrow, newcol) == NULL || B.lookup(newrow, newcol)->color != p.color))
		{
			newB = B.copy();
			(*newB).move(row, col, newrow, newcol);
			NewBoards.push_back((*newB));
		}
		// Up 2, Right 1
		newrow = row - 2;
		newcol = col + 1;
		if(is_valid(newrow, newcol) && (B.lookup(newrow, newcol) == NULL || B.lookup(newrow, newcol)->color != p.color))
		{
			newB = B.copy();
			(*newB).move(row, col, newrow, newcol);
			NewBoards.push_back((*newB));
		}
		// Up 1, Left 2
		newrow = row - 1;
		newcol = col - 2;
		if(is_valid(newrow, newcol) && (B.lookup(newrow, newcol) == NULL || B.lookup(newrow, newcol)->color != p.color))
		{
			newB = B.copy();
			(*newB).move(row, col, newrow, newcol);
			NewBoards.push_back((*newB));
		}
		// Up 1, Right 2
		newrow = row - 1;
		newcol = col + 2;
		if(is_valid(newrow, newcol) && (B.lookup(newrow, newcol) == NULL || B.lookup(newrow, newcol)->color != p.color))
		{
			newB = B.copy();
			(*newB).move(row, col, newrow, newcol);
			NewBoards.push_back((*newB));
		}
		// Down 2, Left 1
		newrow = row + 2;
		newcol = col - 1;
		if(is_valid(newrow, newcol) && (B.lookup(newrow, newcol) == NULL || B.lookup(newrow, newcol)->color != p.color))
		{
			newB = B.copy();
			(*newB).move(row, col, newrow, newcol);
			NewBoards.push_back((*newB));
		}
		// Down 2, Right 1
		newrow = row + 2;
		newcol = col + 1;
		if(is_valid(newrow, newcol) && (B.lookup(newrow, newcol) == NULL || B.lookup(newrow, newcol)->color != p.color))
		{
			newB = B.copy();
			(*newB).move(row, col, newrow, newcol);
			NewBoards.push_back((*newB));
		}
		// Down 1, Left 2
		newrow = row + 1;
		newcol = col - 2;
		if(is_valid(newrow, newcol) && (B.lookup(newrow, newcol) == NULL || B.lookup(newrow, newcol)->color != p.color))
		{
			newB = B.copy();
			(*newB).move(row, col, newrow, newcol);
			NewBoards.push_back((*newB));
		}
		// Down 1, Right 2
		newrow = row + 1;
		newcol = col + 2;
		if(is_valid(newrow, newcol) && (B.lookup(newrow, newcol) == NULL || B.lookup(newrow, newcol)->color != p.color))
		{
			newB = B.copy();
			(*newB).move(row, col, newrow, newcol);
			NewBoards.push_back((*newB));
		}
	}
	if(p.name == BISHOP) 
	{
		int newcol = col - 1;
		// top left diagonal
		for(int newrow = newrow - 1; 0 <= newrow; newrow++)
		{
			if(is_valid(newrow, newcol) && (B.lookup(newrow, newcol) == NULL))
			{
				newB = B.copy();
				(*newB).move(row, col, row, newcol);
				NewBoards.push_back((*newB));
			}
			if(is_valid(newrow, newcol) && (B.lookup(newrow, newcol) != NULL))
			{
				if(B.lookup(newrow, newcol)->color != p.color)
				{
					newB = B.copy();
					(*newB).move(row, col, row, newcol);
					NewBoards.push_back((*newB));
				}
				newrow = -1;
			}
			newcol--;
		}
		// top right diagonal
		newcol = col + 1
		for(int newrow = newrow - 1; 0 <= newrow; newrow++)
		{
			if(is_valid(newrow, newcol) && (B.lookup(newrow, newcol) == NULL))
			{
				newB = B.copy();
				(*newB).move(row, col, row, newcol);
				NewBoards.push_back((*newB));
			}
			if(is_valid(newrow, newcol) && (B.lookup(newrow, newcol) != NULL))
			{
				if(B.lookup(newrow, newcol)->color != p.color)
				{
					newB = B.copy();
					(*newB).move(row, col, row, newcol);
					NewBoards.push_back((*newB));
				}
				newrow = -1;
			}
			newcol--;
		}
		// bottom left diagonal
		for()
		// bottom right diagonal
		for()

	}
	if(p.name == QUEEN) {return NewBoards;}
	if(p.name == KING) {return NewBoards;}
	return NewBoards;


}

std::vector<ChessBoard> gen_all_next_main(ChessBoard B, int color)
{
	std::vector<ChessBoard>NewBoards;

	for(int row = 0; row < 8; row++)
	{
		for(int col = 0; col < 8; col++)
		{
			Piece *p = B.lookup(row, col);

			if(p != NULL)
			{
				if(p->color == color)
				{
					return NewBoards;
				}
			}
		}
	}
}

int maxi(ChessBoard B, int depth)
{
	if(depth <= 0) return evaluate();

	int max = INT_MIN;

	std::vector<ChessBoard>NewBoards = gen_all_next_main(B, WHITE);
}