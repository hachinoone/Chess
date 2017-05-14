#include "naiveAI.h"

Move naiveAI::makeAMove(const ChessBoard &cb) {
	vector<Move> allMoves = findAllPossibleMove(cb, poss);
	int n = allMoves.size();
	return allMoves[rand() % n];
}

int main() {
	ChessBoard cb;
	naiveAI ai;
	cb.print();
	int nowx, nowy, nextx, nexty;
	while (1) {
		scanf("%d %d %d %d", &nowx, &nowy, &nextx, &nexty);
		status s = cb.move(nowx, nowy, nextx, nexty);
		while (s == INVALID) {
			puts("Invalid Move!, ReInput Your Move!");
			scanf("%d %d %d %d", &nowx, &nowy, &nextx, &nexty);
			s = cb.move(nowx, nowy, nextx, nexty);
		}
		cb.print();
		if (s == WIN) {
			puts("You Win");
			break;
		}
		Move move = ai.makeAMove(cb);
		nowx = move.nowx;
		nowy = move.nowy;
		nextx = move.nextx;
		nexty = move.nexty;
		printf("%d %d %d %d\n", nowx, nowy, nextx, nexty);
		s = cb.move(nowx, nowy, nextx, nexty);
		while (s == INVALID) {
			puts("Invalid Move!, ReInput Your Move!");
			Move move = ai.makeAMove(cb);
			nowx = move.nowx;
			nowy = move.nowy;
			nextx = move.nextx;
			nexty = move.nexty;
			s = cb.move(nowx, nowy, nextx, nexty);
		}
		cb.print();
		if (s == WIN) {
			puts("You Lose");
			break;
		}
	}
}
