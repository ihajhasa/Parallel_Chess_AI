#include <iostream>
#include "../board_rep.h"
#include "../minimax.h"

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
    cin >> oldrow;
    std::cout << "Enter Current Piece Column [0-7] (left to right)" << std::endl;
    cin >> oldcol;
    std::cout << "Enter New Piece Row [0-7] (up to down)" << std::endl;
    cin >> newrow;
    std::cout << "Enter New Piece Column [0-7] (left to right)" << std::endl;
    cin >> newcol;

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

void process_AI(ChessBoard *B, int color, int depth)
{
    Move nextmove;

    nextmove = Generate_Next(*B, depth, color);

    (*B).move(oldrow, oldcol, newrow, newcol);
}


int main (int argc, char** argv) {

    // Parse arguments
    //  -w :: user wants to control white pieces
    //  -b :: user wants to control black pieces

    int is_AI_white = 1, is_AI_black = 1;
    int AI_depth = 5;

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

    if(is_AI_white) (*B).set_AI_color(WHITE);
    if(is_AI_black) (*B).set_AI_color(BLACK);

    int finished = 0;
    int turn = WHITE;

    while(!finished)
    {

        if(turn == WHITE)
        {
            if(!is_AI_white) process_user(B, turn);
            else process_AI(B, turn, AI_depth);
        }
        else if (turn == BLACK)
        {
            if(!is_AI_black) process_user(B, turn);
            else process_AI(B, turn, AI_depth);
        }

        turn = (turn != WHITE) ? WHITE : BLACK;

    }

}