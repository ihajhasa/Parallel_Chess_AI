#include "../minimax_openmp.h"
#include "../board_rep.h"

int main()
{
	ChessBoard *B = new ChessBoard;
	B->init();

	MiniMaxParallel *AI = new MiniMaxParallel;
	int color = WHITE;


	// for(int i = 0; i < 3; i++)
	// {
		Move mv;
		mv = AI->Generate_Next(*B, 3, color);
		B->move(mv.Old.row, mv.Old.col, mv.New.row, mv.New.col);
		color = (color != WHITE) ? WHITE : BLACK; 
	// }

	delete AI;
	(*B).free_board();
	delete B;
}