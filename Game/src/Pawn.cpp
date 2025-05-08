#include "../include/ChessPieces.h"
#include "../include/ChessBoard.h"

/**********Constructor && Destructor *************/
Pawn::Pawn(PieceColor c, std::string p) : Piece(c, p) {
    Kind = pawn;
    MoveWithTwoSquares = false;
    PieceVal = 1;
}

Pawn::~Pawn() {}
/************************************************/

/***************Helper Functions*****************/
bool Pawn::MoveForward(std::string& move, ChessBoard& Board) {
    /*
     * validation of moving forward 1 or 2 steps at current position
     */

    int DeltaX = move[0] - pos[0]; // differance in Xdirection between current positon and the potintial move
    int DeltaY = move[1] - pos[1]; // differance in Ydirection between current positon and the potintial move
    bool result = false;

    if (Board[move] == nullptr) { // make sure the target is empty square
        if (DeltaX == 0) { // make sure the move is in the right direction
            if (Color == White) { // handle it if it white pawn
                if (DeltaY == 1) result = true;
                else if (DeltaY == 2 && pos[1] == '2' && Board[{pos[0], '3'}] == nullptr) { // handle first move if with 2 square displacement
                    result = true;
                }
            }
            else if (Color == Black) { // same handle but for Black Pawn (moving in the opposite Ydirection)
                if (DeltaY == -1) result = true;
                else if (DeltaY == -2 && pos[1] == '7' && Board[{pos[0], '6'}] == nullptr) {
                    result = true;
                }
            }
        }
    }

    return result;
}

bool Pawn::IsEnPassant(std::string& move, ChessBoard& Board) {
    /*
     * Detecting Possible EnPassant in current position
     */
    int DeltaX = move[0] - pos[0];
    int DeltaY = move[1] - pos[1];
    bool result = false;

    if (Board[move] == nullptr && (DeltaX == -1 || DeltaX == 1)) { // make sure the target position is empty square
        std::string adjacentPawnPos = { move[0], pos[1] }; // finding the square with potintial pawn to capture
        if (Board[adjacentPawnPos] != nullptr && Board[adjacentPawnPos]->GetKind() == pawn && Board[adjacentPawnPos]->GetColor() != Color) {
            // make sure if the potintial square is meeting all the EnPssant conditions
            Pawn* opponentPawn = dynamic_cast<Pawn*>(Board[adjacentPawnPos]);
            if (opponentPawn && opponentPawn->MoveWithTwoSquares == true) {
                if ((Color == White && DeltaY == 1) || (Color == Black && DeltaY == -1)) { // testing for both black and white
                    result = true;
                }
            }
        }
    }
    return result;
}

bool Pawn::PawnCapture(std::string& move, ChessBoard& Board) {
    /*
     * test the validation of possible capture by pawn
     */
    int DeltaX = move[0] - pos[0];
    int DelatY = move[1] - pos[1];

    if (Board[move] != nullptr && Color != Board[move]->GetColor() && (DeltaX == -1 || DeltaX == 1)) {
        if ((Color == White && DelatY == 1) || (Color == Black && DelatY == -1)) {
            return true;
        }
    }
    return false;
}
/***********************************************************/

/***************Class Interface******************/
Action Pawn::IsValidMove(std::string& move, ChessBoard& Board) {
    /*
     * test the validation of move by pawn with all possible ways
     */

    Action result = invalidMove; // store the stste of the move

    // checking all possibalites
    if (MoveForward(move, Board)) result = Move;
    else if (IsEnPassant(move, Board)) result = EnPassent;
    else if (PawnCapture(move, Board)) result = Capture;

    return result;
}

int Pawn::updateAllValidMoves(ChessBoard& Board) {
    /*
     * getting all possible moves for that piece at the current position
     */
    ValidMovesAtPosition.clear(); // clearing the old moves
    MoveWithTwoSquares = false; // MoveWithTwoSquare is true only when the move is played immeditily only
    Action MoveState = invalidMove; // each move state or expected action
    std::string testMove = pos;

    // traversing over all the potintial positions
    // with each position test if it check or not if the the move itself is valid
    if((pos[1] == '2' && Board[pos]->GetColor() == White) || (pos[1] == '7' && Board[pos]->GetColor() == Black)){ // move with two square test
        testMove[1] = pos[1] + (Color == White ? 2 : -2);
        MoveState = IsValidMove(testMove, Board);
        if (MoveState != invalidMove) if (!Board.WouldBeInCheckAfterMove(pos, testMove, Board[pos]->GetColor()))
            ValidMovesAtPosition.push_back(std::make_pair(testMove, MoveState));
    }

    testMove[1] = pos[1] + (Color == White ? 1 : -1); // moves with one square or EnPassant

    MoveState = IsValidMove(testMove, Board);
    if (MoveState != invalidMove) if (!Board.WouldBeInCheckAfterMove(pos, testMove, Board[pos]->GetColor(), (MoveState == EnPassent)))
        ValidMovesAtPosition.push_back(std::make_pair(testMove, MoveState));

    if (pos[0] != 'a') {
        testMove[0] = pos[0] - 1;
        MoveState = IsValidMove(testMove, Board);
        if (MoveState != invalidMove) if (!Board.WouldBeInCheckAfterMove(pos, testMove, Board[pos]->GetColor(), (MoveState == EnPassent)))
            ValidMovesAtPosition.push_back(std::make_pair(testMove, MoveState));
    }

    if (pos[0] != 'h') {
        testMove[0] = pos[0] + 1;
        MoveState = IsValidMove(testMove, Board);
        if (MoveState != invalidMove)
            if (!Board.WouldBeInCheckAfterMove(pos, testMove, Board[pos]->GetColor(), (MoveState == EnPassent)))
                ValidMovesAtPosition.push_back(std::make_pair(testMove, MoveState));
    }

    return (int)ValidMovesAtPosition.size(); // return the number of all valid moves for that pawn
}
/*****************************************************/
