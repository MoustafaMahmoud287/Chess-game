#ifndef CHESSPIECES_H
#define CHESSPIECES_H
#include "ChessDefinitions.h"

class ChessBoard; //declartion of the class that represent the board

/******************abstract class of the Piece ************************/
class Piece {
protected:

	PieceKind Kind;
	PieceColor Color;
	std::string pos;
	int PieceVal;

	virtual Action IsValidMove(std::string& move, ChessBoard& Board) {
		return invalidMove;
	}

	friend class ChessBoard;
	friend class Game;
    friend class AlphaBetaPruner;

public:
    std::vector<std::pair<std::string, Action>> ValidMovesAtPosition;
	Piece(PieceColor c, std::string p) :Color(c), pos(p), Kind(empty), PieceVal(0), ValidMovesAtPosition(0) {};

    virtual ~Piece() {};

    virtual void MoveTo(std::string& NewPos, bool undo = false) {
		pos = NewPos;
	}

	virtual int updateAllValidMoves(ChessBoard& Board) { return 0; }
	virtual PieceKind GetKind() { return Kind; }
	virtual std::string GetPositon() { return pos; }
	virtual PieceColor GetColor() { return Color; }
};
/**************************************************************************/

/**************** Drived Pawn Class form Piece ****************************/
class Pawn : public Piece {
private:

	bool MoveForward(std::string& move, ChessBoard& Board);
	bool IsEnPassant(std::string& move, ChessBoard& Board);
	bool PawnCapture(std::string& move, ChessBoard& Board);
	Action IsValidMove(std::string& move, ChessBoard& Board);

public:
	int updateAllValidMoves(ChessBoard& Board);
	bool MoveWithTwoSquares;
    void MoveTo(std::string& NewPos, bool undo = false) {
		if (abs(pos[1] - NewPos[1]) == 2) MoveWithTwoSquares = true;
        pos = NewPos;
	}
	Pawn(PieceColor c, std::string p);
	~Pawn();
};
/**************************************************************************/

class Bishop : public Piece {
private:
	Action IsValidMove(std::string& move, ChessBoard& Board);
	friend class Queen;
public:
	int updateAllValidMoves(ChessBoard& Board);
	Bishop(PieceColor c, std::string p);
	~Bishop();
};

class Knight : public Piece {
private:
	Action IsValidMove(std::string& move, ChessBoard& Board);
public:
	int updateAllValidMoves(ChessBoard& Board);
	Knight(PieceColor c, std::string p);
	~Knight();
};

class Rook : public Piece {
private:
    bool previousMovedBefore;
	Action IsValidMove(std::string& move, ChessBoard& Board);
	friend class Queen;
	friend class King;
    friend class AlphaBetaPruner;
public:
    bool MovedBefore;
    bool FirstMove() {return MovedBefore;}
    void MoveTo(std::string& NewPos, bool undo = false) {
        pos = NewPos;
        if(undo){
            MovedBefore = previousMovedBefore;
        }
        else{
            previousMovedBefore = MovedBefore;
            MovedBefore = true;
        }
	}
	int updateAllValidMoves(ChessBoard& Board);
	Rook(PieceColor c, std::string p);
	~Rook();
};

class Queen : public Piece {
private:
	Rook VirtualRook;
	Bishop VirtualBishop;
	Action IsValidMove(std::string& move, ChessBoard& Board);
public:
	int updateAllValidMoves(ChessBoard& Board);
    void MoveTo(std::string& NewPos, bool undo = false) {
        pos = NewPos;
        VirtualRook.pos = NewPos;
        VirtualBishop.pos = NewPos;
    }
	Queen(PieceColor c, std::string p);
	~Queen();
};

class King : public Piece {
private:
    bool previousMovedBefore;
	Action IsValidMove(std::string& move, ChessBoard& Board);
    friend class AlphaBetaPruner;
public:
    bool MovedBefore;
    bool FirstMove() {return MovedBefore;}
	int updateAllValidMoves(ChessBoard& Board);
    void MoveTo(std::string& NewPos, bool undo = false) {
		pos = NewPos;
        if(undo){
            MovedBefore = previousMovedBefore;
        }
        else{
            previousMovedBefore = MovedBefore;
            MovedBefore = true;
        }
	}
	King(PieceColor c, std::string p);
	~King();
};
#endif

