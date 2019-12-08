#ifndef MINMAX
#define MINMAX

#include "board_rep.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <limits.h>
#include <vector>

int maxi(ChessBoard B, int depth); // White
int mini(ChessBoard B, int depth); // Black

#endif