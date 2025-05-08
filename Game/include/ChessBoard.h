#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "ChessDefinitions.h"
class Piece;

class ChessBoard
{
private:
	std::vector<std::vector<Piece*>> ActualBoard;
    std::string lastFrom;
    std::string lastTo;
    Action lastAction;
    PieceKind lastCaptured;
	std::string WhiteKingPosition;
	std::string BlackKingPosition;
	friend class Piece;
	friend class Game;
    friend class AlphaBetaPruner;
	bool checkedByPawn(std::string square, PieceColor attacker);
	bool checkedByBishopOrQueen(std::string square, PieceColor attacker);
	bool checkedByRookOrQueen(std::string square, PieceColor attacker);
	bool checkedByKnight(std::string square, PieceColor attacker);
	bool checkedByKing(std::string square, PieceColor attacker);
    void UpdateKingPosition(const std::string& from, const std::string& to);
public:
	ChessBoard(InitialPositon TYPE = STANDARD_BOARD);
    ChessBoard(ChessBoard& board);
	~ChessBoard();
    bool IsCheckedSquare(std::string square, PieceColor attacker);
	Piece*& operator[](std::string pos);
    bool WouldBeInCheckAfterMove(std::string from, std::string to, PieceColor playerColor, bool isEnPassant = false);
	void UpdateBoard(std::string from, std::string to, Action action);
    void UndoMove();
};

#endif
