#ifndef ALPHABETA_PRUNER_H
#define ALPHABETA_PRUNER_H

#include "ChessDefinitions.h"

class ChessBoard;
class Piece;

class AlphaBetaPruner {

private:
    int maxDepth_;
    Piece* capturedPiece_;
    std::string capturedPos_;
    std::string rookFrom_;
    std::string rookTo_;

    int alphaBeta(ChessBoard board, int depth, int alpha, int beta, bool maximizingPlayer, PieceColor aiColor);
    int evaluateBoard(ChessBoard board, PieceColor aiColor, bool anyMoves);
    int getPieceValue(PieceKind kind);
    PieceColor getOppositeColor(PieceColor color);

public:
    AlphaBetaPruner(int maxDepth);
    std::pair<std::string, std::string> findBestMove(ChessBoard board, PieceColor aiColor);
};

#endif // ALPHABETA_PRUNER_H
