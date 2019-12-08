#include <iostream>
#include "../board_rep.h"
#include "../minimax.h"

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

int is_valid_move(ChessBoard *B, int color, int oldrow, int oldcol, int newrow, int newcol)
{
    Piece *p, *tmp;

    p = (*B).lookup(oldrow, oldcol);

    if(p == NULL) return 0; // empty square

    if(p->color != color) return 0; // piece is owned by other player

    tmp = (*B).lookup(newrow, newcol);

    if(tmp == NULL) return 1; // The new square is empty

    if(tmp != NULL && tmp->color != color) return 1; // the new square is occupied by opponent piece

    return 0;

}

void process_user(ChessBoard *B, int color)
{
    int oldrow, oldcol, newrow, newcol;

    std::cout << "Enter Current Piece Row [0-7] (up to down)" << std::endl;
    std::cin >> oldrow;
    std::cout << "Enter Current Piece Column [0-7] (left to right)" << std::endl;
    std::cin >> oldcol;
    std::cout << "Enter New Piece Row [0-7] (up to down)" << std::endl;
    std::cin >> newrow;
    std::cout << "Enter New Piece Column [0-7] (left to right)" << std::endl;
    std::cin >> newcol;

    if(is_valid_move(B, color, oldrow, oldcol, newrow, newcol))
    {
        (*B).move(oldrow, oldcol, newrow, newcol);
    }
    else
    {
        std::cout << "Not valid, please enter a valid move" << std::endl;
        process_user(B, color);
    }
}

void process_AI(ChessBoard *B, MiniMax AI, int color, int depth)
{
    Move nextmove;

    nextmove = AI.Generate_Next(*B, depth, color);

    (*B).move(nextmove.Old.row, nextmove.Old.col, nextmove.New.row, nextmove.New.col);
    std::cout << "Moved (" << nextmove.Old.row << ", " << nextmove.Old.col << ") to (" << nextmove.New.row << ", " << nextmove.New.col << ")" << std::endl;
    
}


int main (int argc, char** argv) {

    // Parse arguments
    //  -w :: user wants to control white pieces
    //  -b :: user wants to control black pieces

    int is_AI_white = 1, is_AI_black = 1;
    int AI_depth = 5;
    MiniMax AI_White, AI_Black;

    for(int i = 1; i < argc; i++)
    {
        if(!strcmp(argv[i], "-w"))
            is_AI_white = 0;

        else if(!strcmp(argv[i], "-b"))
            is_AI_black = 0;

        else if(!strcmp(argv[i], "-d"))
            AI_depth = atoi(argv[i + 1]);
            
    }

    // Done parsing arguments ---------------------


    ChessBoard *B = new ChessBoard;
    (*B).init();

    print_board(*B);

    if(is_AI_white) (*B).set_AI_color(WHITE);
    if(is_AI_black) (*B).set_AI_color(BLACK);

    int finished = 0;
    int turn = WHITE;

    while(!finished)
    {

        if(turn == WHITE)
        {
            if(!is_AI_white) process_user(B, turn);
            else process_AI(B, AI_White, turn, AI_depth);
        }
        else if (turn == BLACK)
        {
            if(!is_AI_black) process_user(B, turn);
            else process_AI(B, AI_Black, turn, AI_depth);
        }

        print_board(*B);

        turn = (turn != WHITE) ? WHITE : BLACK;

    }

}