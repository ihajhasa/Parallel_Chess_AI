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

void setup_board1(ChessBoard *B1)
{
	(*B1).empty_board();
	(*B1).set_piece(0, 2, KING, WHITE);
	(*B1).set_piece(0, 4, KNIGHT, BLACK);
	(*B1).set_piece(1, 0, ROOK, WHITE);
	(*B1).set_piece(2, 1, KING, BLACK);
	(*B1).set_piece(2, 5, BISHOP, BLACK);
}

void setup_board2(ChessBoard *B1)
{
	(*B1).empty_board();
	(*B1).set_piece(1, 6, QUEEN, WHITE);
	(*B1).set_piece(1, 7, QUEEN, WHITE);
	(*B1).set_piece(2, 2, KNIGHT, BLACK);
	(*B1).set_piece(2, 6, KNIGHT, BLACK);
	(*B1).set_piece(2, 7, BISHOP, WHITE);
	(*B1).set_piece(3, 5, QUEEN, WHITE);
	(*B1).set_piece(4, 5, KNIGHT, WHITE);
	(*B1).set_piece(7, 3, BISHOP, WHITE);
}

void setup_board3(ChessBoard *B1)
{
	(*B1).empty_board();
	(*B1).set_piece(1, 6, QUEEN, WHITE);
	(*B1).set_piece(1, 7, QUEEN, WHITE);
	(*B1).set_piece(2, 2, PAWN, BLACK);
	(*B1).set_piece(2, 6, KNIGHT, BLACK);
	(*B1).set_piece(2, 7, BISHOP, WHITE);
	(*B1).set_piece(3, 5, QUEEN, WHITE);
	(*B1).set_piece(4, 5, KNIGHT, WHITE);
	(*B1).set_piece(7, 3, BISHOP, WHITE);
}


int main()
{

	// Making board 1
	ChessBoard *B1 = new ChessBoard;
	(*B1).init();
	setup_board3(B1);

	double minimax_sequential_time = 0, minimax_openmp_time = 0;

	std::cout << "Board 1" << std::endl;
	std::cout << "------------------------------------" << std::endl;

	for(int i = 0; i < 3; i++)
	{
		Timer t;
		t.reset();
		MiniMax AI;
		Move rmv;

		rmv = AI.Generate_Next(*B1, 5, BLACK);

		minimax_sequential_time += t.elapsed();

	}

	minimax_sequential_time = minimax_sequential_time/3.0;
	std::cout << "MiniMax Sequential Time:\t" << minimax_sequential_time << "ms" << std::endl;
	

	for(int i = 0; i < 1; i++)
	{
		Timer t;
		t.reset();
		MiniMaxParallel AI;
		Move rmv;

		rmv = AI.Generate_Next(*B1, 5, BLACK);

		if(i == 0)
		{
			B1->move(rmv.Old.row, rmv.Old.col, rmv.New.row, rmv.New.col);
			print_board(*B1);
			B1->move(rmv.New.row, rmv.New.col, rmv.Old.row, rmv.Old.col);
		}

		minimax_openmp_time += t.elapsed();

	}

	minimax_openmp_time = minimax_openmp_time/3.0;
	std::cout << "MiniMax OpenMP Time:\t\t" << minimax_openmp_time << "ms" << std::endl;
	std::cout << "Achieved Speedup OpenMP:\t" << (minimax_sequential_time/minimax_openmp_time) << "x speedup" << std::endl << std::endl;

	(*B1).free_board();
	delete B1;
	return 0;
	// // Making board 2
	// (*B1).free_board();
	// B1 = new ChessBoard;
	// (*B1).init();
	// (*B1).empty_board();
	// (*B1).set_piece(0, 1, QUEEN, WHITE);
	// (*B1).set_piece(2, 0, QUEEN, BLACK);
	// (*B1).set_piece(1, 3, QUEEN, WHITE);
	// (*B1).set_piece(5, 2, QUEEN, BLACK);
	// (*B1).set_piece(7, 5, QUEEN, BLACK);
	// (*B1).set_piece(6, 7, QUEEN, BLACK);
	// (*B1).set_piece(3, 4, QUEEN, WHITE);
	// (*B1).set_piece(4, 6, QUEEN, WHITE);

	// minimax_sequential_time = 0; minimax_openmp_time = 0;

	// std::cout << "Board 2" << std::endl;
	// std::cout << "------------------------------------" << std::endl;

	// for(int i = 0; i < 3; i++)
	// {
	// 	Timer t;
	// 	t.reset();
	// 	MiniMax AI;
	// 	Move rmv;

	// 	rmv = AI.Generate_Next(*B1, 3, WHITE);

	// 	minimax_sequential_time += t.elapsed();

	// }

	
	// minimax_sequential_time = minimax_sequential_time/3.0;
	// std::cout << "MiniMax Sequential Time:\t" << minimax_sequential_time << "ms" << std::endl;

	// for(int i = 0; i < 3; i++)
	// {
	// 	Timer t;
	// 	t.reset();
	// 	MiniMaxParallel AI;
	// 	Move rmv;

	// 	rmv = AI.Generate_Next(*B1, 3, WHITE);

	// 	minimax_openmp_time += t.elapsed();

	// }

	// minimax_openmp_time = minimax_openmp_time/3.0;
	// std::cout << "MiniMax OpenMP Time:\t\t" << minimax_openmp_time << "ms" << std::endl;
	// std::cout << "Achieved Speedup OpenMP:\t" << (minimax_sequential_time/minimax_openmp_time) << "x speedup" << std::endl;

	// (*B1).free_board();
	// free(B1);
	// return 0;

}