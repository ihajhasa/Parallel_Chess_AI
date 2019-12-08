#include "../minimax.h"
#include "../board_rep.h"

void print_piece(Piece *p_p)
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

void print_board(ChessBoard B)
{
	std::cout << "-----------------------------------------" << std::endl;
	for(int row = 0; row < 8; row++)
	{
		for(int col = 0; col < 8; col++)
		{
			std::cout << "| ";
			print_piece(B.lookup(row, col));
		}
		std::cout << "|" << std::endl;
		std::cout << "-----------------------------------------" << std::endl;
	}
	std::cout << std::endl << std::endl;
}

int main()
{
	ChessBoard *B = new ChessBoard;
	(*B).init();

	std::vector<Move> moves = gen_all_next_moves(*B, WHITE);

	for (std::vector<Move>::iterator it = moves.begin(); it != moves.end(); ++it)
	{
		ChessBoard *B2 = (*B).copy();
		(*B2).move((*it).oldrow, (*it).oldcol, (*it).newrow, (*it).newcol);
		print_board(*B2);
		// (*B2).free_board();
	}

}