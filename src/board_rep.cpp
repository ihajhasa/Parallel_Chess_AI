#include "board_rep.h"

/*---------------------------------------------------------------------------*/
/*	Piece functions															 */
/*---------------------------------------------------------------------------*/

int Piece_getname(Piece p)
{
	return p.name;
}

int Piece_getcolor(Piece p)
{
	return p.color;
}

void Piece_free(Piece* p)
{
	if(p != NULL) free(p);
}

/*---------------------------------------------------------------------------*/
/*	ChessBoard functions													 */
/*---------------------------------------------------------------------------*/

void ChessBoard::set_AI_color(int color)
{
	if(color == BLACK) is_AI_black = 1;
	else is_AI_white = 1;
}

int ChessBoard::is_white()
{
	return is_AI_white;
}

int ChessBoard::is_black()
{
	return is_AI_black;
}

void ChessBoard::reset()
{
	for(int row = 0; row < 8; row++)
	{
		for(int col = 0; col < 8; col++)
		{
			board[row][col] = NULL;
		}
	}

	// position black and white pawns
	for(int col = 0; col < 8; col++)
	{
		board[1][col] = Black[PAWN];
		board[6][col] = White[PAWN];
	}

	// Setting up remaining black pieces
	board[0][0] = Black[ROOK];
	board[0][1] = Black[KNIGHT];
	board[0][2] = Black[BISHOP];
	board[0][3] = Black[KING];
	board[0][4] = Black[QUEEN];
	board[0][5] = Black[BISHOP];
	board[0][6] = Black[KNIGHT];
	board[0][7] = Black[ROOK];

	// Setting up remaining white pieces
	board[7][0] = White[ROOK];
	board[7][1] = White[KNIGHT];
	board[7][2] = White[BISHOP];
	board[7][3] = White[QUEEN];
	board[7][4] = White[KING];
	board[7][5] = White[BISHOP];
	board[7][6] = White[KNIGHT];
	board[7][7] = White[ROOK];
}

void ChessBoard::init()
{
	initialize();
	reset();
}

Piece* ChessBoard::set_piece(int row, int col, int name, int color)
{
	return set(row, col, name, color);
}


Piece* ChessBoard::lookup(int row, int col)
{
	return lookup_square(row, col);
}

Piece* ChessBoard::move(int oldrow, int oldcol, int newrow, int newcol)
{
	return move_piece(oldrow, oldcol, newrow, newcol);
}

ChessBoard* ChessBoard::copy()
{
	ChessBoard *newaddr = new ChessBoard;
	(*newaddr).init();

	for(int row = 0; row < 8; row++)
	{
		for(int col = 0; col < 8; col++)
		{
			Piece* p = lookup_square(row, col);
			if(p != NULL)
			{
				(*newaddr).set(row, col,p->name,p->color);
			}
		}
	}

	return newaddr;
}

void ChessBoard::free_board()
{
	if(initialized_pieces)
	{
		for(int i = 0; i < 6; i++)
		{
			Piece_free(White[i]);
			Piece_free(Black[i]);
		}
	}
}




