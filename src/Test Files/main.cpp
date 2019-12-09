#include "board_rep.h"
#include "minimax.h"
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

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

	MiniMax AI;

	// print_board(*B);

	ChessBoard *B_ = (*B).copy();

	std::cout << "Color of the AI: WHITE\n\n";

	std::cout << "Generating First Move..." << "\n\n";
	
	Move fmvW = AI.Generate_Next(*B, 10, WHITE);

	AI.print_move (*B, fmvW);

	std::cout << "\n\n";
	(*B).move(fmvW.Old.row, fmvW.Old.col, fmvW.New.row, fmvW.New.col);

	print_board(*B);

	std::cout << "Color of the 2nd AI: BLACK\n\n";

	std::cout << "Generating First Move..." << "\n\n";
	
	Move fmvB = AI.Generate_Next(*B, 10, BLACK);

	AI.print_move (*B, fmvB);

	std::cout << "\n\n";
	(*B).move(fmvB.Old.row, fmvB.Old.col, fmvB.New.row, fmvB.New.col);

	print_board(*B);

	return 0;
}