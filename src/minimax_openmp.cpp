#include "minimax_openmp.h"

#define GRANULARITY 15

void MiniMaxParallel::print_move(ChessBoard board, Move move)
{
	std::cout << "Moving Piece: ";
	find_piece(board, move.Old);
	std::cout << "\n";
	std::cout << "(" << std::to_string(move.Old.row) << ", " << std::to_string(move.Old.col) << ")";
	std::cout << " to ";
	std::cout << "(" << std::to_string(move.New.row) << ", " << std::to_string(move.New.col) << ")";
	std::cout << "\n";
	return;
}

Best_Move linear_get_max(std::vector<Best_Move> scores, int low, int high)
{
	int max = low;

	for(int i = low + 1; i < high; i++)
	{
		max = (scores[i].score > scores[max].score) ? i : max;
	}

	return scores[max];
}

Best_Move fast_get_max(std::vector<Best_Move> scores, int low, int high)
{
	if(high - low < GRANULARITY)
	{
		return linear_get_max(scores, low, high);
	}

	int mid = (high - low) + low/2;

	// Potential for parallelism
	Best_Move min1 = fast_get_max(scores, low, mid);
	Best_Move min2 = fast_get_max(scores, mid, high);

	return (min1.score > min2.score) ? min1 : min2;
}

Best_Move parallel_max(ChessBoard board, int depth, Move move, int color)
{
	if(depth == 0)
	{
		Best_Move bm;
		bm.move = move;
		bm.score = evaluate(board, color);
		return bm;
	}

	std::vector<Move> moves;
	std::vector<Best_Move>moves_score;

	moves = All_Next_Moves(board, color);
	moves_score.resize(moves.size());

	#pragma omp for
	for (int i = 0; i < moves.size(); ++i)
	{
		ChessBoard bc = *(board.copy());
		Move mv = moves[i];
		bc.move(mv.Old.row, mv.Old.col, mv.New.row, mv.New.col);
		moves_score[i] = parallel_max(board, depth-1, mv, (color != WHITE) ? WHITE : BLACK);
	}

	Best_Move max_score = fast_get_max(moves_score, 0, moves_score.size());
	return max_score;

}

Best_Move linear_get_min(std::vector<Best_Move> scores, int low, int high)
{
	int min = low;

	for(int i = low + 1; i < high; i++)
	{
		min = (scores[i].score < scores[min].score) ? i : min;
	}

	return scores[min];
}

Best_Move fast_get_min(std::vector<Best_Move> scores, int low, int high)
{
	if(high - low < GRANULARITY)
	{
		return linear_get_min(scores, low, high);
	}

	int mid = (high - low) + low/2;

	// Potential for parallelism
	Best_Move min1 = fast_get_min(scores, low, mid);
	Best_Move min2 = fast_get_min(scores, mid, high);

	return (min1.score < min2.score) ? min1 : min2;
}

Best_Move parallel_min(ChessBoard board, int depth, Move move, int color)
{
	if(depth == 0)
	{
		Best_Move bm;
		bm.move = move;
		bm.score = evaluate(board, color);
		return bm;
	}

	std::vector<Move> moves;
	std::vector<Best_Move>moves_score;

	moves = All_Next_Moves(board, color);
	moves_score.resize(moves.size());

	#pragma omp for
	for (int i = 0; i < moves.size(); ++i)
	{
		ChessBoard bc = *(board.copy());
		Move mv = moves[i];
		bc.move(mv.Old.row, mv.Old.col, mv.New.row, mv.New.col);
		moves_score[i] = parallel_max(board, depth-1, mv, (color != WHITE) ? WHITE : BLACK);
	}

	Best_Move min_score = fast_get_min(moves_score, 0, moves_score.size());
	return min_score;

}


Move MiniMaxParallel::Generate_Next(ChessBoard board, int depth, int color)
{
	Best_Move Optimal = parallel_max(board, depth, create_move(0,0,0,0), color);
	return Optimal.move;
}