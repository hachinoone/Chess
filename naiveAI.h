#ifndef _NAIVE_AI_H
#define _NAIVE_AI_H
#include <ctime>
#include <cstdlib>
#include "basic.h"
struct naiveAI {
	chess_posession poss;
	naiveAI(chess_posession cp = BLACK) {
		poss = cp;
		srand(time(NULL));
	}
	Move makeAMove(const ChessBoard&);
};
#endif
