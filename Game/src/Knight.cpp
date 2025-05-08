#include "../include/ChessPieces.h"
#include "../include/ChessBoard.h"

Knight::Knight(PieceColor c, std::string p) : Piece(c, p){
    Kind = knight;
    PieceVal = 3;
}

Knight::~Knight() {}


Action Knight::IsValidMove(std::string& move, ChessBoard& Board) {
    /*
     * validation of knight moves
     */
    Action result = invalidMove;
    if (Board[move] == nullptr) result = Move;
    else if (Board[move]->GetColor() != Color) result = Capture;

    return result;
}

int Knight::updateAllValidMoves(ChessBoard& Board) {

    ValidMovesAtPosition.clear();
    Action MoveState = invalidMove;

    const int directions[8][2] = { {2,1},
                                  {2,-1},
                                  {-2,1},
                                  {-2,-1},
                                  {1,2},
                                  {1,-2},
                                  {-1,2},
                                  {-1,-2}
    }; // all possible kinght moves in all directions

    for (const auto& dir : directions)  {

        std::string testMove = pos; // the knight jukps immeditaly so we test one move in every direction only
        testMove[0] += dir[0];
        testMove[1] += dir[1];

        if (isInBounds(testMove[0], testMove[1])) {
            MoveState = IsValidMove(testMove, Board);
            if (MoveState != invalidMove)
            if (!Board.WouldBeInCheckAfterMove(pos, testMove, Board[pos]->GetColor()))
                ValidMovesAtPosition.push_back(std::make_pair(testMove, MoveState));
        }

    }

    return (int)ValidMovesAtPosition.size(); // nnumber of all valid moves from the knight
}
