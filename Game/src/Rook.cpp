#include "../include/ChessPieces.h"
#include "../include/ChessBoard.h"

Rook::Rook(PieceColor c, std::string p) : Piece(c, p) {
    Kind = rook;
    PieceVal = 5;
    MovedBefore = false;
}

Rook::~Rook() {}

Action Rook::IsValidMove(std::string& move, ChessBoard& Board) {
    /*
     * test the validation of move between rook
     */
    if (move == pos || !isInBounds(move[0], move[1])) { // if the position is invalid return
        return invalidMove;
    }

    int DeltaX = move[0] - pos[0];
    int DeltaY = move[1] - pos[1];

    if (DeltaX  != 0 && DeltaY != 0) { // rook could move while change is in one direction
        return invalidMove;
    }

    int hStep = (DeltaX != 0) ? (DeltaX > 0 ? 1 : -1) : 0; // determining the step depends on the DeltaX
    int vStep = (DeltaY != 0) ? (DeltaY > 0 ? 1 : -1) : 0; // determining the step depends on the DeltaY

    std::string testPos = pos;
    while (true) {
        testPos[0] += hStep;
        testPos[1] += vStep;

        if (testPos == move) {
            break;
        }

        if (Board[testPos] != nullptr) {
            //if there is any pieces before getting the target position
            return invalidMove;
        }
    }

    Piece* target = Board[move];
    if (target == nullptr) {
        // if the target is empty square
        return Move;
    }
    if (target->GetColor() != Color) {
        // if the target is a opponent piece
        return Capture;
    }

    return invalidMove;
}

int Rook::updateAllValidMoves(ChessBoard& Board) {
    ValidMovesAtPosition.clear();

    const int directions[4][2] = { // getting all the position the rook could move to
        {1, 0},   // Right
        {-1, 0},  // Left
        {0, 1},   // Up
        {0, -1}   // Down
    };

    for (const auto& dir : directions) { // iterating over all the directions
        std::string testMove = pos;

        while (true) {
            testMove[0] += dir[0];
            testMove[1] += dir[1];

            if (!isInBounds(testMove[0], testMove[1])) {
                break;
            }

            Action moveState = IsValidMove(testMove, Board);
            if (moveState != invalidMove) {
                // Verify move doesn't leave king in check
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
