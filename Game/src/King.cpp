#include "../include/ChessPieces.h"
#include "../include/ChessBoard.h"

King::King(PieceColor c, std::string p) : Piece(c, p) {
    Kind = king;
    MovedBefore = false;
    PieceVal = INT_MAX;
}

King::~King() {}

Action King::IsValidMove(std::string& move, ChessBoard& Board) {
    PieceColor attacker = (Color == White ? Black : White);
    Action result = invalidMove;

    // Long castle
    if (move[0] <= 'c' && !MovedBefore) {
        std::string aSquare = GetSquare('a', pos[1]);
        std::string bSquare = GetSquare('b', pos[1]);
        std::string cSquare = GetSquare('c', pos[1]);
        std::string dSquare = GetSquare('d', pos[1]);

        Piece* prook = Board[aSquare];
        if (prook && prook->GetKind() == rook && !static_cast<Rook*>(prook)->MovedBefore) {
            if (!Board[aSquare] || !Board[bSquare] || !Board[cSquare] || !Board[dSquare]) {
                if (!Board[bSquare] && !Board[cSquare] && !Board[dSquare]) {
                    if (!Board.IsCheckedSquare(pos, attacker) &&
                        !Board.IsCheckedSquare(dSquare, attacker) &&
                        !Board.IsCheckedSquare(cSquare, attacker)) {
                        result = LongCastle;
                    }
                }
            }
        }
    }

    // Short castle
    else if (move[0] >= 'g' && !MovedBefore) {
        std::string fSquare = GetSquare('f', pos[1]);
        std::string gSquare = GetSquare('g', pos[1]);
        std::string hSquare = GetSquare('h', pos[1]);

        Piece* prook = Board[hSquare];
        if (prook && prook->GetKind() == rook && !static_cast<Rook*>(prook)->MovedBefore) {
            if (!Board[fSquare] && !Board[gSquare]) {
                if (!Board.IsCheckedSquare(pos, attacker) &&
                    !Board.IsCheckedSquare(fSquare, attacker) &&
                    !Board.IsCheckedSquare(gSquare, attacker)) {
                    result = ShortCastle;
                }
            }
        }
    }

    // Normal King Move
    else {
        if (Board[move] == nullptr)
            result = Move;
        else if (Board[move]->GetColor() != Color)
            result = Capture;
    }

    return result;
}

int King::updateAllValidMoves(ChessBoard& Board) {
    ValidMovesAtPosition.clear();

    Action MoveState = invalidMove;

    int directions[8][2] = {
        {0,1},{0,-1},{1,0},{-1,0},
        {1,1},{1,-1},{-1,1},{-1,-1}
    };

    for (int i = 0; i < 8; i++) {
        std::string testMove = pos;
        testMove[0] += directions[i][0];
        testMove[1] += directions[i][1];

        if (testMove[0] >= 'a' && testMove[0] <= 'h' &&
            testMove[1] >= '1' && testMove[1] <= '8') {
            MoveState = IsValidMove(testMove, Board);
            if (MoveState != invalidMove) {
                if (!Board.WouldBeInCheckAfterMove(pos, testMove, Color))
                    ValidMovesAtPosition.emplace_back(testMove, MoveState);
            }
        }
    }

    // Castling
    if (!MovedBefore) {
        std::string longCastleMove = GetSquare('c', pos[1]);
        if (IsValidMove(longCastleMove, Board) == LongCastle) {
            ValidMovesAtPosition.emplace_back(longCastleMove, LongCastle);
        }

        std::string shortCastleMove = GetSquare('g', pos[1]);
        if (IsValidMove(shortCastleMove, Board) == ShortCastle) {
            ValidMovesAtPosition.emplace_back(shortCastleMove, ShortCastle);
        }
    }

    return (int)ValidMovesAtPosition.size();
}
