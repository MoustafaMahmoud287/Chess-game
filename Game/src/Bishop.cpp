#include "../include/ChessPieces.h"
#include "../include/ChessBoard.h"

Bishop::Bishop(PieceColor c, std::string p) : Piece(c, p) {
    Kind = bishop;
    PieceVal = 3;
}

Bishop::~Bishop() {}

Action Bishop::IsValidMove(std::string& move, ChessBoard& Board) {
    /*
    * move validation for a bishop
    */
    if (move == pos || !isInBounds(move[0], move[1])) { // move is in the board
        return invalidMove;
    }

    int DletaX = move[0] - pos[0];
    int DletaY = move[1] - pos[1];

    if (abs(DletaX) != abs(DletaY)) {
        return invalidMove;
    }

    int hStep = (DletaX > 0) ? 1 : -1;
    int vStep = (DletaY > 0) ? 1 : -1;

    std::string testPos = pos;
    while (true) {
        testPos[0] += hStep;
        testPos[1] += vStep;

        if (testPos == move) {
            break;
        }

        if (Board[testPos] != nullptr) {
            return invalidMove;
        }
    }

    Piece* target = Board[move];
    if (target == nullptr) {
        return Move;
    }
    if (target->GetColor() != Color) {
        return Capture;
    }

    return invalidMove;
}

int Bishop::updateAllValidMoves(ChessBoard& Board) {
    ValidMovesAtPosition.clear();

    const int directions[4][2] = {
        {1, 1},    // Up-right
        {1, -1},   // Down-right
        {-1, 1},   // Up-left
        {-1, -1}   // Down-left
    };

    for (const auto& dir : directions) {
        std::string testMove = pos;

        while (true) {
            testMove[0] += dir[0];
            testMove[1] += dir[1];

            if (!isInBounds(testMove[0], testMove[1])) {
                break;
            }

            Action moveState = IsValidMove(testMove, Board);
            if (moveState != invalidMove) {
                if (!Board.WouldBeInCheckAfterMove(pos, testMove, Color)) {
                    ValidMovesAtPosition.emplace_back(testMove, moveState);
                }
            }

            if (Board[testMove] != nullptr) {
                break;
            }
        }
    }

    return static_cast<int>(ValidMovesAtPosition.size());
}
