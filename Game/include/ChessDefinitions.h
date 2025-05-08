#ifndef CHESS_DEFINITIONS_H
#define CHESS_DEFINITIONS_H

#include<iostream>
#include<vector>
#include<string.h>
#include<math.h>
#include <climits>
#include <algorithm>
#include <utility>
#include <stack>

enum PieceKind {
	empty,
	pawn,  
	rook,
	knight,
	bishop,
	queen,
	king
};

enum PieceColor { White, Black};

enum CurrentState { Alive, Killed };

enum SquareColor { Light, Dark};

enum Action{invalidMove, Move, Capture, ShortCastle, LongCastle, Check, OutOfTime, EnPassent};

enum GameState{ CheckMate, StaleMate, Draw, KeepPlying, Promote };

enum BoardColumns {

    // standard chess naming
	A, B, C, D, E, F, G, H

};

enum BoardRows {

	// standard chess naming
	_1, _2, _3, _4, _5, _6, _7, _8
};

enum InitialPositon { STANDARD_BOARD, EMPTY_BOARD  /*used in for Board constructor*/ };

static std::string GetSquare(char file, char rank) {
	return std::string(1, file) + rank;
}

static std::string GetPos1(int file, int rank){
    return GetSquare(('a'+file), ('1'+rank));
}

static bool isInBounds(char file, char rank) {
    return file >= 'a' && file <= 'h' && rank >= '1' && rank <= '8';
}
#endif
