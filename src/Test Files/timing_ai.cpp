#include "../minimax.h"
#include "../minimax_openmp.h"
#include "../timing.h"


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

	// Making board 1
	ChessBoard *B1 = new ChessBoard;
	(*B1).init();
	(*B1).empty_board();
	(*B1).set_piece(0, 2, KING, WHITE);
	(*B1).set_piece(0, 4, KNIGHT, BLACK);
	(*B1).set_piece(1, 0, ROOK, WHITE);
	(*B1).set_piece(2, 1, KING, BLACK);
	(*B1).set_piece(2, 5, BISHOP, BLACK);

	double minimax_sequential_time = 0, minimax_openmp_time = 0;

	std::cout << "Board 1" << std::endl;
	std::cout << "------------------------------------" << std::endl;

	for(int i = 0; i < 3; i++)
	{
		Timer t;
		t.reset();
		MiniMax AI;
		Move rmv;

		rmv = AI.Generate_Next(*B1, 7, WHITE);

		minimax_sequential_time += t.elapsed();

	}

	minimax_sequential_time = minimax_sequential_time/3.0;
	std::cout << "MiniMax Sequential Time:\t" << minimax_sequential_time << "ms" << std::endl;
	

	for(int i = 0; i < 3; i++)
	{
		Timer t;
		t.reset();
		MiniMaxParallel AI;
		Move rmv;

		rmv = AI.Generate_Next(*B1, 7, WHITE);

		minimax_openmp_time += t.elapsed();

	}

	minimax_openmp_time = minimax_openmp_time/3.0;
	std::cout << "MiniMax OpenMP Time:\t\t" << minimax_openmp_time << "ms" << std::endl;
	std::cout << "Achieved Speedup OpenMP:\t" << (minimax_sequential_time/minimax_openmp_time) << "x speedup" << std::endl << std::endl;


	// Making board 2
	(*B1).free_board();
	B1 = new ChessBoard;
	(*B1).init();
	(*B1).empty_board();
	(*B1).set_piece(0, 1, QUEEN, WHITE);
	(*B1).set_piece(2, 0, QUEEN, BLACK);
	(*B1).set_piece(1, 3, QUEEN, WHITE);
	(*B1).set_piece(5, 2, QUEEN, BLACK);
	(*B1).set_piece(7, 5, QUEEN, BLACK);
	(*B1).set_piece(6, 7, QUEEN, BLACK);
	(*B1).set_piece(3, 4, QUEEN, WHITE);
	(*B1).set_piece(4, 6, QUEEN, WHITE);

	minimax_sequential_time = 0; minimax_openmp_time = 0;

	std::cout << "Board 2" << std::endl;
	std::cout << "------------------------------------" << std::endl;

	for(int i = 0; i < 3; i++)
	{
		Timer t;
		t.reset();
		MiniMax AI;
		Move rmv;

		rmv = AI.Generate_Next(*B1, 3, WHITE);

		minimax_sequential_time += t.elapsed();

	}

	
	minimax_sequential_time = minimax_sequential_time/3.0;
	std::cout << "MiniMax Sequential Time:\t" << minimax_sequential_time << "ms" << std::endl;

	for(int i = 0; i < 3; i++)
	{
		Timer t;
		t.reset();
		MiniMaxParallel AI;
		Move rmv;

		rmv = AI.Generate_Next(*B1, 3, WHITE);

		minimax_openmp_time += t.elapsed();

	}

	minimax_openmp_time = minimax_openmp_time/3.0;
	std::cout << "MiniMax OpenMP Time:\t\t" << minimax_openmp_time << "ms" << std::endl;
	std::cout << "Achieved Speedup OpenMP:\t" << (minimax_sequential_time/minimax_openmp_time) << "x speedup" << std::endl;

	(*B1).free_board();
	free(B1);
	return 0;

}