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
					if (!g[nowx][i].isEmpty) cnt++;
					if (cnt > 1) break;
				}
				if (cnt > 1) return INVALID;
				if (cnt == 1 && g[nextx][nexty].isEmpty) return INVALID;
			} else {
				int minx = min(nowx, nextx);
				int maxx = nowx + nextx - minx;
				int cnt = 0;
				for (int i = minx + 1; i < maxx; i++) {
					if (!g[i][nowy].isEmpty) cnt++;
					if (cnt > 1) break;
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
			if (!g[nowx + (dx / 2)][nowy + (dy / 2)].isEmpty) return INVALID;
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
					chessPosition pos1(nextx, nexty, g[nextx][nexty].chess);
					remainChess[(cp + 1) & 1].erase(pos1);
					g[nextx][nexty].setChess(g[nowx][nowy].chess);
					chessPosition pos2(nowx, nowy, g[nowx][nowy].chess);
					remainChess[cp].erase(pos2);
					chessPosition pos3(nextx, nexty, g[nextx][nexty].chess);
					remainChess[cp].insert(pos3);
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
	if (!g[nextx][nexty].isEmpty && g[nextx][nexty].chess.type == KING) res = WIN;
	chessPosition pos(nextx, nexty, g[nextx][nexty].chess);
	remainChess[(cp + 1) & 1].erase(pos);
	g[nextx][nexty].setChess(g[nowx][nowy].chess);
	chessPosition pos2(nowx, nowy, g[nowx][nowy].chess);
	remainChess[cp].erase(pos2);
	chessPosition pos3(nextx, nexty, g[nextx][nexty].chess);
	remainChess[cp].insert(pos3);
	g[nowx][nowy].setEmpty();
	if (nowMove == RED) {
		nowMove = BLACK;
	} else {
		nowMove = RED;
	}
	return res;
}
vector<Move> findAllPossibleMove(const ChessBoard &cb, chess_posession cp) {
	set<chessPosition>::iterator it;
	vector<Move> res;
	int nowx;
	int nowy;
	int nextx;
	int nexty;
	for (it = cb.remainChess[cp].begin(); it != cb.remainChess[cp].end(); it++) {
		nowx = it -> x;
		nowy = it -> y;
		Chess chess = it -> chess;
		printf("%d %d %d\n", nowx, nowy, chess.type);
		switch (chess.type) {
			case PAWN: {
				if (chess.posession == RED) {
					if (nowy < 9) {
						if (cb.g[nowx][nowy + 1].isEmpty || cb.g[nowx][nowy + 1].chess.posession != cp) {
							Move newMove(nowx, nowy, nowx, nowy + 1);
							res.push_back(newMove);
						}
					}
					if (nowy > 4) {
						if (nowx < 8) {
							if (cb.g[nowx + 1][nowy].isEmpty || cb.g[nowx + 1][nowy].chess.posession != cp) {
								Move newMove(nowx, nowy, nowx + 1, nowy);
								res.push_back(newMove);
							}
						}
						if (nowx > 0) {
							if (cb.g[nowx - 1][nowy].isEmpty || cb.g[nowx - 1][nowy].chess.posession != cp) {
								Move newMove(nowx, nowy, nowx - 1, nowy);
								res.push_back(newMove);
							}
						}
					}
				} else {
					if (nowy > 0) {
						if (cb.g[nowx][nowy - 1].isEmpty || cb.g[nowx][nowy - 1].chess.posession != cp) {
							Move newMove(nowx, nowy, nowx, nowy - 1);
							res.push_back(newMove);
						}
					}
					if (nowy < 5) {
						if (nowx < 8) {
							if (cb.g[nowx + 1][nowy].isEmpty || cb.g[nowx + 1][nowy].chess.posession != cp) {
								Move newMove(nowx, nowy, nowx + 1, nowy);
								res.push_back(newMove);
							}
						}
						if (nowx > 0) {
							if (cb.g[nowx - 1][nowy].isEmpty || cb.g[nowx - 1][nowy].chess.posession != cp) {
								Move newMove(nowx, nowy, nowx - 1, nowy);
								res.push_back(newMove);
							}
						}
					}
				}
				break;
			}
			case GUN: {
				int cnt = 0;
				for (int i = nowx - 1; i >= 0; i--) {
					if (!cb.g[i][nowy].isEmpty) {
						cnt++;
						if (cnt == 1) continue;
						if (cb.g[i][nowy].chess.posession != cp) {
							Move newMove(nowx, nowy, i, nowy);
							res.push_back(newMove);
						}
						break;
					}
					if (cnt == 0) {
						Move newMove(nowx, nowy, i, nowy);
						res.push_back(newMove);
					}
				}
				cnt = 0;
				for (int i = nowx + 1; i < 10; i++) {
					if (!cb.g[i][nowy].isEmpty) {
						cnt++;
						if (cnt == 1) continue;
						if (cb.g[i][nowy].chess.posession != cp) {
							Move newMove(nowx, nowy, i, nowy);
							res.push_back(newMove);
						}
						break;
					}
					if (cnt == 0) {
						Move newMove(nowx, nowy, i, nowy);
						res.push_back(newMove);
					}
				}
				cnt = 0;
				for (int i = nowy - 1; i >= 0; i--) {
					if (!cb.g[nowx][i].isEmpty) {
						cnt++;
						if (cnt == 1) continue;
						if (cb.g[nowx][i].chess.posession != cp) {
							Move newMove(nowx, nowy, nowx, i);
							res.push_back(newMove);
						}
						break;
					}
					if (cnt == 0) {
						Move newMove(nowx, nowy, nowx, i);
						res.push_back(newMove);
					}
				}
				cnt = 0;
				for (int i = nowy + 1; i < 10; i++) {
					if (!cb.g[nowx][i].isEmpty) {
						cnt++;
						if (cnt == 1) continue;
						if (cb.g[nowx][i].chess.posession != cp) {
							Move newMove(nowx, nowy, nowx, i);
							res.push_back(newMove);
						}
						break;
					}
					if (cnt == 0) {
						Move newMove(nowx, nowy, nowx, i);
						res.push_back(newMove);
					}
				}
				break;
			}
			case ROOK: {
				if (nowx == 8 && nowy == 9)	puts("1");
				for (int i = nowx - 1; i >= 0; i--) {
					if (!cb.g[i][nowy].isEmpty && cb.g[i][nowy].chess.posession == cp) break; 
					Move newMove(nowx, nowy, i, nowy);
					res.push_back(newMove);
					if (!cb.g[i][nowy].isEmpty) break;
				}
				for (int i = nowx + 1; i < 10; i++) {
					if (!cb.g[i][nowy].isEmpty && cb.g[i][nowy].chess.posession == cp) break; 
					Move newMove(nowx, nowy, i, nowy);
					res.push_back(newMove);
					if (!cb.g[i][nowy].isEmpty) break;
				}
				for (int i = nowy - 1; i >= 0; i--) {
					if (!cb.g[nowx][i].isEmpty && cb.g[nowx][i].chess.posession == cp) break; 
					Move newMove(nowx, nowy, nowx, i);
					res.push_back(newMove);
					if (!cb.g[nowx][i].isEmpty) break;
				}
				for (int i = nowy + 1; i < 10; i++) {
					if (!cb.g[nowx][i].isEmpty && cb.g[nowx][i].chess.posession == cp) break; 
					Move newMove(nowx, nowy, nowx, i);
					res.push_back(newMove);
					if (!cb.g[nowx][i].isEmpty) break;
				}
				break;
			}
			case KNIGHT: {
				nextx = nowx + 2; nexty = nowy + 1;
				if (nextx < 10 && nextx >= 0 && nexty < 10 && nexty >= 0) {
					if (cb.g[nextx][nexty].isEmpty || cb.g[nextx][nexty].chess.posession != cp) {
						if (cb.g[nowx + 1][nowy].isEmpty) {
							Move newMove(nowx, nowy, nextx, nexty);
							res.push_back(newMove);
						}	
					}
				}
				nextx = nowx + 2; nexty = nowy - 1;
				if (nextx < 10 && nextx >= 0 && nexty < 10 && nexty >= 0) {
					if (cb.g[nextx][nexty].isEmpty || cb.g[nextx][nexty].chess.posession != cp) {
						if (cb.g[nowx + 1][nowy].isEmpty) {
							Move newMove(nowx, nowy, nextx, nexty);
							res.push_back(newMove);
						}	
					}
				}
				nextx = nowx + 1; nexty = nowy + 2;
				if (nextx < 10 && nextx >= 0 && nexty < 10 && nexty >= 0) {
					if (cb.g[nextx][nexty].isEmpty || cb.g[nextx][nexty].chess.posession != cp) {
						if (cb.g[nowx][nowy + 1].isEmpty) {
							Move newMove(nowx, nowy, nextx, nexty);
							res.push_back(newMove);
						}	
					}
				}
				nextx = nowx + 1; nexty = nowy - 2;
				if (nextx < 10 && nextx >= 0 && nexty < 10 && nexty >= 0) {
					if (cb.g[nextx][nexty].isEmpty || cb.g[nextx][nexty].chess.posession != cp) {
						if (cb.g[nowx][nowy - 1].isEmpty) {
							Move newMove(nowx, nowy, nextx, nexty);
							res.push_back(newMove);
						}	
					}
				}
				nextx = nowx - 1; nexty = nowy + 2;
				if (nextx < 10 && nextx >= 0 && nexty < 10 && nexty >= 0) {
					if (cb.g[nextx][nexty].isEmpty || cb.g[nextx][nexty].chess.posession != cp) {
						if (cb.g[nowx][nowy + 1].isEmpty) {
							Move newMove(nowx, nowy, nextx, nexty);
							res.push_back(newMove);
						}	
					}
				}
				nextx = nowx - 1; nexty = nowy - 2;
				if (nextx < 10 && nextx >= 0 && nexty < 10 && nexty >= 0) {
					if (cb.g[nextx][nexty].isEmpty || cb.g[nextx][nexty].chess.posession != cp) {
						if (cb.g[nowx][nowy - 1].isEmpty) {
							Move newMove(nowx, nowy, nextx, nexty);
							res.push_back(newMove);
						}	
					}
				}
				nextx = nowx - 2; nexty = nowy + 1;
				if (nextx < 10 && nextx >= 0 && nexty < 10 && nexty >= 0) {
					if (cb.g[nextx][nexty].isEmpty || cb.g[nextx][nexty].chess.posession != cp) {
						if (cb.g[nowx - 1][nowy].isEmpty) {
							Move newMove(nowx, nowy, nextx, nexty);
							res.push_back(newMove);
						}	
					}
				}
				nextx = nowx - 2; nexty = nowy - 1;
				if (nextx < 10 && nextx >= 0 && nexty < 10 && nexty >= 0) {
					if (cb.g[nextx][nexty].isEmpty || cb.g[nextx][nexty].chess.posession != cp) {
						if (cb.g[nowx - 1][nowy].isEmpty) {
							Move newMove(nowx, nowy, nextx, nexty);
							res.push_back(newMove);
						}	
					}
				}
				break;
			}
			case BISHOP: {
				int maxy;
				int miny;
				if (cp == RED) {
					maxy = 5;
					miny = 0;
				} else {
					maxy = 10;
					miny = 5;
				}
				nextx = nowx + 2; nexty = nowy + 2;
				if (nextx < 10 && nextx >= 0 && nexty < maxy && nexty >= miny) {
					if (cb.g[nextx][nexty].isEmpty || cb.g[nextx][nexty].chess.posession != cp) {
						if (cb.g[nowx + 1][nowy + 1].isEmpty) {
							Move newMove(nowx, nowy, nextx, nexty);
							res.push_back(newMove);
						}	
					}
				}
				nextx = nowx + 2; nexty = nowy - 2;
				if (nextx < 10 && nextx >= 0 && nexty < maxy && nexty >= miny) {
					if (cb.g[nextx][nexty].isEmpty || cb.g[nextx][nexty].chess.posession != cp) {
						if (cb.g[nowx + 1][nowy - 1].isEmpty) {
							Move newMove(nowx, nowy, nextx, nexty);
							res.push_back(newMove);
						}	
					}
				}
				nextx = nowx - 2; nexty = nowy + 2;
				if (nextx < 10 && nextx >= 0 && nexty < maxy && nexty >= miny) {
					if (cb.g[nextx][nexty].isEmpty || cb.g[nextx][nexty].chess.posession != cp) {
						if (cb.g[nowx - 1][nowy + 1].isEmpty) {
							Move newMove(nowx, nowy, nextx, nexty);
							res.push_back(newMove);
						}	
					}
				}
				nextx = nowx - 2; nexty = nowy - 2;
				if (nextx < 10 && nextx >= 0 && nexty < maxy && nexty >= miny) {
					if (cb.g[nextx][nexty].isEmpty || cb.g[nextx][nexty].chess.posession != cp) {
						if (cb.g[nowx + 1][nowy + 1].isEmpty) {
							Move newMove(nowx, nowy, nextx, nexty);
							res.push_back(newMove);
						}
					}
				}
				break;
			}
			case QUEEN: {
				int minx = 3;
				int maxx = 6;
				int miny;
				int maxy;
				if (cp == RED) {
					maxy = 3;
					miny = 0;
				} else {
					maxy = 10;
					miny = 7;
				}
				nextx = nowx + 1; nexty = nowy + 1;
				if (nextx < maxx && nextx >= minx && nexty < maxy && nexty >= miny) {
					if (cb.g[nextx][nexty].isEmpty || cb.g[nextx][nexty].chess.posession != cp) {
						Move newMove(nowx, nowy, nextx, nexty);
						res.push_back(newMove);
					}
				}
				nextx = nowx - 1; nexty = nowy + 1;
				if (nextx < maxx && nextx >= minx && nexty < maxy && nexty >= miny) {
					if (cb.g[nextx][nexty].isEmpty || cb.g[nextx][nexty].chess.posession != cp) {
						Move newMove(nowx, nowy, nextx, nexty);
						res.push_back(newMove);
					}
				}
				nextx = nowx + 1; nexty = nowy - 1;
				if (nextx < maxx && nextx >= minx && nexty < maxy && nexty >= miny) {
					if (cb.g[nextx][nexty].isEmpty || cb.g[nextx][nexty].chess.posession != cp) {
						Move newMove(nowx, nowy, nextx, nexty);
						res.push_back(newMove);
					}
				}
				nextx = nowx - 1; nexty = nowy - 1;
				if (nextx < maxx && nextx >= minx && nexty < maxy && nexty >= miny) {
					if (cb.g[nextx][nexty].isEmpty || cb.g[nextx][nexty].chess.posession != cp) {
						Move newMove(nowx, nowy, nextx, nexty);
						res.push_back(newMove);
					}
				}
				break;
			}
			case KING: {
				int minx = 3;
				int maxx = 6;
				int miny;
				int maxy;
				if (cp == RED) {
					maxy = 3;
					miny = 0;
				} else {
					maxy = 10;
					miny = 7;
				}
				nextx = nowx + 1; nexty = nowy;
				if (nextx < maxx && nextx >= minx && nexty < maxy && nexty >= miny) {
					if (cb.g[nextx][nexty].isEmpty || cb.g[nextx][nexty].chess.posession != cp) {
						Move newMove(nowx, nowy, nextx, nexty);
						res.push_back(newMove);
					}
				}
				nextx = nowx - 1; nexty = nowy;
				if (nextx < maxx && nextx >= minx && nexty < maxy && nexty >= miny) {
					if (cb.g[nextx][nexty].isEmpty || cb.g[nextx][nexty].chess.posession != cp) {
						Move newMove(nowx, nowy, nextx, nexty);
						res.push_back(newMove);
					}
				}
				nextx = nowx; nexty = nowy + 1;
				if (nextx < maxx && nextx >= minx && nexty < maxy && nexty >= miny) {
					if (cb.g[nextx][nexty].isEmpty || cb.g[nextx][nexty].chess.posession != cp) {
						Move newMove(nowx, nowy, nextx, nexty);
						res.push_back(newMove);
					}
				}
				nextx = nowx; nexty = nowy - 1;
				if (nextx < maxx && nextx >= minx && nexty < maxy && nexty >= miny) {
					if (cb.g[nextx][nexty].isEmpty || cb.g[nextx][nexty].chess.posession != cp) {
						Move newMove(nowx, nowy, nextx, nexty);
						res.push_back(newMove);
					}
				}
				if (cp == RED) {
					for (int i = nowy + 1; i < 10; i++) {
						if (!cb.g[nowx][i].isEmpty) {
							if (cb.g[nowx][i].chess.type == KING) {
								Move newMove(nowx, nowy,nowx, i);
								res.push_back(newMove);
							} else {
								break;
							}
						}
					}
				} else {
					for (int i = nowy - 1; i >= 0; i--) {
						if (!cb.g[nowx][i].isEmpty) {
							if (cb.g[nowx][i].chess.type == KING) {
								Move newMove(nowx, nowy,nowx, i);
								res.push_back(newMove);
							} else {
								break;
							}
						}
					}
				}
				break;
			}
			default: break;
		}
	}
	return res;
}
int main() {
	ChessBoard cb;
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
