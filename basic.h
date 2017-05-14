#ifndef _BASIC_H
#define _BASIC_H
#include <cstdio>
#include <vector> 
#include <set>
using namespace std;
char upper_to_lower(char);
enum status {
	WIN,
	VALID,
	INVALID
};
enum chess_posession {
	RED = 0,
	BLACK = 1
};
enum chess_type {
	PAWN,
	ROOK,
	KNIGHT,
	GUN,
	BISHOP,
	QUEEN,
	KING
}; 
struct Chess {
	chess_posession posession;
	chess_type type;
	Chess(chess_posession p = RED, chess_type t = PAWN) {
		posession = p;
		type = t;
	}
};
const Chess R_PAWN(RED, PAWN);
const Chess R_ROOK(RED, ROOK);
const Chess R_KNIGHT(RED, KNIGHT);
const Chess R_GUN(RED, GUN);
const Chess R_BISHOP(RED, BISHOP);
const Chess R_QUEEN(RED, QUEEN);
const Chess R_KING(RED, KING);
const Chess B_PAWN(BLACK, PAWN);
const Chess B_ROOK(BLACK, ROOK);
const Chess B_KNIGHT(BLACK, KNIGHT);
const Chess B_GUN(BLACK, GUN);
const Chess B_BISHOP(BLACK, BISHOP);
const Chess B_QUEEN(BLACK, QUEEN);
const Chess B_KING(BLACK, KING);
struct Grid {
	bool isEmpty;
	Chess chess;
	Grid() {
		isEmpty = true;
	}
	Grid(bool i, Chess c) {
		isEmpty = i;
		if (!isEmpty) chess = c;
	}
	void setChess(Chess c) {
		isEmpty = false;
		chess = c;
	}
	void setEmpty() {
		isEmpty = true;
	}
	void print() {
		if (isEmpty) {
			putchar(' ');
		} else {
			char ch;
			switch (chess.type) {
				case PAWN: {
					ch = 'P';
					break;
				}
				case ROOK: {
					ch = 'R';
					break;
				}
				case KNIGHT: {
					ch = 'M';
					break;
				}
				case GUN: {
					ch = 'G';
					break;
				}
				case BISHOP: {
					ch = 'B';
					break;
				}
				case QUEEN: {
					ch = 'Q';
					break;
				}
				default: ch = 'K';
			}
			if (chess.posession == BLACK) ch = upper_to_lower(ch);
			putchar(ch);
		}
	}
};
struct chessPosition {
	Chess chess;
	int x;
	int y;
	chessPosition() {}
	chessPosition(int x_, int y_, Chess c) {
		x = x_;
		y = y_;
		chess = c;
	}
	bool operator<(const chessPosition& other) const {
		if (x == other.x) return y < other.y;
		return x < other.x;
	}
};
struct ChessBoard {
	Grid g[9][10];
	set<chessPosition> remainChess[2];
	chess_posession nowMove;
	void print() {
		for (int i = 9; i >= 0; i--) {
			for (int j = 0; j < 9; j++) {
				g[j][i].print();
			}
			puts("");
		}
	}
	void reset() {
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 10; j++) g[i][j].setEmpty();
		nowMove = RED;
		remainChess[0].clear();
		remainChess[1].clear();
		chessPosition R_ROOK_1(0, 0, R_ROOK);
		chessPosition R_KNIGHT_1(1, 0, R_KNIGHT);
		chessPosition R_BISHOP_1(2, 0, R_BISHOP);
		chessPosition R_QUEEN_1(3, 0, R_QUEEN);
		chessPosition R_KING_1(4, 0, R_KING);
		chessPosition R_QUEEN_2(5, 0, R_QUEEN);
		chessPosition R_BISHOP_2(6, 0, R_BISHOP);
		chessPosition R_KNIGHT_2(7, 0, R_KNIGHT);
		chessPosition R_ROOK_2(8, 0, R_ROOK);
		chessPosition R_GUN_1(1, 2, R_GUN);
		chessPosition R_GUN_2(7, 2, R_GUN);
		chessPosition R_PAWN_1(0, 3, R_PAWN);
		chessPosition R_PAWN_2(2, 3, R_PAWN);
		chessPosition R_PAWN_3(4, 3, R_PAWN);
		chessPosition R_PAWN_4(6, 3, R_PAWN);
		chessPosition R_PAWN_5(8, 3, R_PAWN);
		chessPosition B_ROOK_1(0, 9, B_ROOK);
		chessPosition B_KNIGHT_1(1, 9, B_KNIGHT);
		chessPosition B_BISHOP_1(2, 9, B_BISHOP);
		chessPosition B_QUEEN_1(3, 9, B_QUEEN);
		chessPosition B_KING_1(4, 9, B_KING);
		chessPosition B_QUEEN_2(5, 9, B_QUEEN);
		chessPosition B_BISHOP_2(6, 9, B_BISHOP);
		chessPosition B_KNIGHT_2(7, 9, B_KNIGHT);
		chessPosition B_ROOK_2(8, 9, B_ROOK);
		chessPosition B_GUN_1(1, 7, B_GUN);
		chessPosition B_GUN_2(7, 7, B_GUN);
		chessPosition B_PAWN_1(0, 6, B_PAWN);
		chessPosition B_PAWN_2(2, 6, B_PAWN);
		chessPosition B_PAWN_3(4, 6, B_PAWN);
		chessPosition B_PAWN_4(6, 6, B_PAWN);
		chessPosition B_PAWN_5(8, 6, B_PAWN);
		remainChess[RED].insert(R_ROOK_1);
		remainChess[RED].insert(R_KNIGHT_1);
		remainChess[RED].insert(R_BISHOP_1);
		remainChess[RED].insert(R_QUEEN_1);
		remainChess[RED].insert(R_KING_1);
		remainChess[RED].insert(R_QUEEN_2);
		remainChess[RED].insert(R_BISHOP_2);
		remainChess[RED].insert(R_KNIGHT_2);
		remainChess[RED].insert(R_ROOK_2);
		remainChess[RED].insert(R_GUN_1);
		remainChess[RED].insert(R_GUN_2);
		remainChess[RED].insert(R_PAWN_1);
		remainChess[RED].insert(R_PAWN_2);
		remainChess[RED].insert(R_PAWN_3);
		remainChess[RED].insert(R_PAWN_4);
		remainChess[RED].insert(R_PAWN_5);
		remainChess[BLACK].insert(B_ROOK_1);
		remainChess[BLACK].insert(B_KNIGHT_1);
		remainChess[BLACK].insert(B_BISHOP_1);
		remainChess[BLACK].insert(B_QUEEN_1);
		remainChess[BLACK].insert(B_KING_1);
		remainChess[BLACK].insert(B_QUEEN_2);
		remainChess[BLACK].insert(B_BISHOP_2);
		remainChess[BLACK].insert(B_KNIGHT_2);
		remainChess[BLACK].insert(B_ROOK_2);
		remainChess[BLACK].insert(B_GUN_1);
		remainChess[BLACK].insert(B_GUN_2);
		remainChess[BLACK].insert(B_PAWN_1);
		remainChess[BLACK].insert(B_PAWN_2);
		remainChess[BLACK].insert(B_PAWN_3);
		remainChess[BLACK].insert(B_PAWN_4);
		remainChess[BLACK].insert(B_PAWN_5);
		g[0][0].setChess(R_ROOK);
		g[1][0].setChess(R_KNIGHT);
		g[2][0].setChess(R_BISHOP);
		g[3][0].setChess(R_QUEEN);
		g[4][0].setChess(R_KING);
		g[5][0].setChess(R_QUEEN);
		g[6][0].setChess(R_BISHOP);
		g[7][0].setChess(R_KNIGHT);
		g[8][0].setChess(R_ROOK);
		g[1][2].setChess(R_GUN);
		g[7][2].setChess(R_GUN);
		g[0][3].setChess(R_PAWN);
		g[2][3].setChess(R_PAWN);
		g[4][3].setChess(R_PAWN);
		g[6][3].setChess(R_PAWN);
		g[8][3].setChess(R_PAWN);
		g[0][9].setChess(B_ROOK);
		g[1][9].setChess(B_KNIGHT);
		g[2][9].setChess(B_BISHOP);
		g[3][9].setChess(B_QUEEN);
		g[4][9].setChess(B_KING);
		g[5][9].setChess(B_QUEEN);
		g[6][9].setChess(B_BISHOP);
		g[7][9].setChess(B_KNIGHT);
		g[8][9].setChess(B_ROOK);
		g[1][7].setChess(B_GUN);
		g[7][7].setChess(B_GUN);
		g[0][6].setChess(B_PAWN);
		g[2][6].setChess(B_PAWN);
		g[4][6].setChess(B_PAWN);
		g[6][6].setChess(B_PAWN);
		g[8][6].setChess(B_PAWN);
	}
	ChessBoard() {
		reset();
	}
	status move(int, int, int, int);
};
struct Move {
	int nowx;
	int nowy;
	int nextx;
	int nexty;
	Move(int x = 0, int y = 0, int nx = 0, int ny = 0) {
		nowx = x;
		nowy = y;
		nextx = nx;
		nexty = ny;
	}
};
vector<Move> findAllPossibleMove(const ChessBoard&, chess_posession);
#endif
