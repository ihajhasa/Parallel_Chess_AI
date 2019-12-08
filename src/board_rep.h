#ifndef BOARD_REP
#define BOARD_REP

#include <iostream>
#include <cstdlib>
#include <algorithm>

#define PAWN	0
#define ROOK	1
#define KNIGHT	2
#define BISHOP	3
#define QUEEN	4
#define KING 	5

#define BLACK	6
#define WHITE	7



struct Piece
{
		int name;
		int color;
};

int Piece_getname(Piece p);
int Piece_getcolor(Piece p);
void Piece_free(Piece p);

class ChessBoard
{
	private:
		int initialized_pieces;

		Piece* White[6];
		Piece* Black[6];

		Piece* board[8][8];

		int AI_color;

		void initialize()
		{
			// Initialize white and black pieces
			for(int i = 0; i < 6; i++)
			{
				White[i] = (Piece*)malloc(sizeof(Piece));
				White[i]->name = i;
				White[i]->color = WHITE;
				Black[i] = (Piece*)malloc(sizeof(Piece));
				Black[i]->name = i;
				Black[i]->color = BLACK;
			}

			for(int row = 0; row < 8; row++)
			{
				for(int col = 0; col < 8; col++)
				{
					board[row][col] = NULL;
				}
			}

			initialized_pieces = 1;
		};

		void clear()
		{
			for(int row = 0; row < 8; row++)
			{
				for(int col = 0; col < 8; col++)
				{
					board[row][col] = NULL;
				}
			}
		};

		void set(int row, int col, int name, int color)
		{
			if(color == BLACK)
				board[row][col] = Black[name];
			else
				board[row][col] = White[name];
			return;
		}

		// if (oldrow, oldcol) is not empty (i.e. NULL) then move piece to
		// (newrow, newcol) and return Piece. O.W. return NULL
		// does NOT check the validity of the move
		Piece* move_piece(int oldrow, int oldcol, int newrow, int newcol)
		{
			// no piece on old location
			if (board[oldrow][oldcol] == NULL) return NULL;

			// out of bounds
			if (oldrow < 0 || 8 <= oldrow) return NULL;
			if (oldcol < 0 || 8 <= oldcol) return NULL;
			if (newrow < 0 || 8 <= newrow) return NULL;
			if (newcol < 0 || 8 <= newcol) return NULL;

			board[newrow][newcol] = board[oldrow][oldcol];
			board[oldrow][oldcol] = NULL;
			return board[newrow][newcol];
		};
		Piece *lookup_square(int row, int col)
		{
			if (row < 0 || 8 <= row) return NULL;
			if (col < 0 || 8 <= col) return NULL;
			return board[row][col];
		};

	public:
		void set_board_color(int color);
		int get_board_color();
		void reset();
		void init();
		Piece* lookup(int row, int col);
		Piece* move(int oldrow, int oldcol, int newrow, int newcol);
		ChessBoard* copy();
		void free_board();
};







#endif