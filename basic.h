#ifndef _BASIC_H
#define _BASIC_H
#include <cstdio>
char upper_to_lower(char);
enum status {
	WIN,
	VALID,
	INVALID
};
enum chess_posession {
	RED,
	BLACK
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
struct ChessBoard {
	Grid g[9][10];
	chess_posession nowMove;
	ChessBoard() {
		nowMove = RED;
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
	status move(int, int, int, int);
};
#endif
