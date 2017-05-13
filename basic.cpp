#include "basic.h" 
#include <iostream>
using std::min;
int abs(int x) {
	if (x < 0) return -x;
	return x;
}
char upper_to_lower(char c) {
	if (c <= 'Z' && c >= 'A') return c - 'A' + 'a';
	return c;
}
status ChessBoard::move(int nowx, int nowy, int nextx, int nexty) {
	chess_posession cp = nowMove;
	if (nowx > 9 || nowx < 0 || nowy > 9 || nowy < 0 ||
		nextx > 9 || nextx < 0 || nexty > 9 || nexty < 0) return INVALID;
	if (nowx == nextx && nowy == nexty) return INVALID;
	if (g[nowx][nowy].isEmpty || g[nowx][nowy].chess.posession != cp) return INVALID;
	if (!g[nextx][nexty].isEmpty && g[nextx][nexty].chess.posession == cp) return INVALID;
	switch (g[nowx][nowy].chess.type) {
		case PAWN: {
			if (cp == RED) {
				if (nowx == nextx) {
					if (nowy + 1 != nexty) return INVALID;
				} else {
					if (nowy < 5) return INVALID;
					if (nowy != nexty) return INVALID;
					if (nowx + 1 != nextx && nowx - 1 != nextx) return INVALID;
				}
			} else {
				if (nowx == nextx) {
					if (nowy - 1 != nexty) return INVALID;
				} else {
					if (nowy > 4) return INVALID;
					if (nowy != nexty) return INVALID;
					if (nowx + 1 != nextx && nowx - 1 != nextx) return INVALID;
				}
			}
			break;
		}
		case GUN: {
			if (nowx != nextx && nowy != nexty) return INVALID;
			if (nowx == nextx) {
				int miny = min(nowy, nexty);
				int maxy = nowy + nexty - miny;
				int cnt = 0;
				for (int i = miny + 1; i < maxy; i++) {
					if (!g[nowx][i].isEmpty) {
						if (g[nowx][i].chess.posession == cp) return INVALID;
						cnt++;
					}
				}
				if (cnt > 1) return INVALID;
				if (cnt == 1 && g[nextx][nexty].isEmpty) return INVALID;
			} else {
				int minx = min(nowx, nextx);
				int maxx = nowx + nextx - minx;
				int cnt = 0;
				for (int i = minx + 1; i < maxx; i++) {
					if (!g[i][nowy].isEmpty) {
						if (g[i][nowy].chess.posession == cp) return INVALID;
						cnt++;
					}
				}
				if (cnt > 1) return INVALID;
				if (cnt == 1 && g[nextx][nexty].isEmpty) return INVALID;
			}
			break;
		}
		case ROOK: {
			if (nowx != nextx && nowy != nexty) return INVALID;
			if (nowx == nextx) {
				int miny = min(nowy, nexty);
				int maxy = nowy + nexty - miny;
				for (int i = miny + 1; i < maxy; i++) {
					if (!g[nowx][i].isEmpty) return INVALID;
				}
			} else {
				int minx = min(nowx, nextx);
				int maxx = nowx + nextx - minx;
				for (int i = minx + 1; i < maxx; i++) {
					if (!g[i][nowy].isEmpty) return INVALID;
				}
			}
			break;
		}
		case KNIGHT: {
			int dx = nextx - nowx;
			int dy = nexty - nowy;
			if (abs(dx) > 2 || abs(dx) < 1 || abs(dy) > 2 || abs(dy) < 1) return INVALID;
			if (!g[nowx + (dx >> 1)][nowy + (dy >> 1)].isEmpty) return INVALID;
			break;
		}
		case BISHOP: {
			if (abs(nextx - nowx) != 2 || abs(nexty - nowy) != 2) return INVALID;
			if (!g[(nowx + nextx) >> 1][(nowy + nexty) >> 1].isEmpty) return INVALID;
			if (g[nowx][nowy].chess.posession == RED) {
				if (nexty > 4) return INVALID;
			} else {
				if (nexty < 5) return INVALID;
			}
			break;
		}
		case QUEEN: {
			if (abs(nextx - nowx) != 1 || abs(nexty - nowy) != 1) return INVALID;
			if (nextx < 3 || nextx > 5) return INVALID;
			if (g[nowx][nowy].chess.posession == RED) {
				if (nexty > 2) return INVALID;
			} else {
				if (nexty < 7) return INVALID;
			}
			break;
		}
		case KING: {
			if (nowx == nextx) {
				if (abs(nexty - nowy) > 1) {
					if (g[nextx][nexty].isEmpty) return INVALID;
					if (g[nextx][nexty].chess.type != KING) return INVALID;
					int miny = nowy, maxy = nowy + nexty - miny;
					for (int i = miny + 1; i < maxy; i++) {
						if (!g[nextx][nexty].isEmpty) return INVALID;
					}
					g[nextx][nexty].setChess(g[nowx][nowy].chess);
					g[nowx][nowy].setEmpty();
					return WIN;
				} else {
					if (nexty == nowy) return INVALID;
					if (nexty > 2 && nexty < 7) return INVALID;
				}
			} else {
				if (abs(nextx - nowx) > 1 || nowy != nexty) return INVALID;
				if (nextx < 3 || nexty > 5) return INVALID;
			}
			break;
		}
	}
	status res = VALID;
	if (g[nextx][nexty].chess.type == KING) res = WIN;
	g[nextx][nexty].setChess(g[nowx][nowy].chess);
	g[nowx][nowy].setEmpty();
	if (nowMove == RED) {
		nowMove = BLACK;
	} else {
		nowMove = RED;
	}
	return res;
}
int main() {
	ChessBoard cb;
	puts("123");
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
			if (cb.nowMove == RED) puts("Black Wins!");
			else puts("Red Wins");
			break;
		}
	}
}
