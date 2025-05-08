#ifndef CHESSGAME_H
#define CHESSGAME_H

#include "ChessDefinitions.h"

class ChessBoard;
class Piece;
class AlphaBetaPruner;

class Game {
private:
	ChessBoard& Board;
	PieceColor PlayerTurn;
	int MoveNumber;
	int AllValidMovesAtPostionCounnter;
	GameState state;
    friend class AlphaBetaPruner;

public:
    bool IsGameOver(){return (AllValidMovesAtPostionCounnter == 0);}
	Game(ChessBoard& B);
	~Game(){};
	void GetGameState();
	void ChangePlayingSide();
    bool IsAnyPromotion();
	bool ApplayMove(std::string moveFrom, std::string moveTo, Action& action, GameState& CurrentState);
};

#endif
