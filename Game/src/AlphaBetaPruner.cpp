#include "../include/AlphaBetaPruner.h"
#include "../include/ChessBoard.h"
#include "../include/ChessGame.h"
#include "../include/ChessPieces.h"

AlphaBetaPruner::AlphaBetaPruner(int maxDepth) : maxDepth_(maxDepth) {}

std::pair<std::string, std::string> AlphaBetaPruner::findBestMove(ChessBoard board, PieceColor aiColor) {
    int alpha = INT_MIN, beta = INT_MAX, bestValue = INT_MIN;
    std::pair<std::string, std::string> bestMove;
    bool anyMoves = false;

    for (char file = 'a'; file <= 'h'; ++file) {
        for (char rank = '1'; rank <= '8'; ++rank) {
            std::string from = {file, rank};
            Piece* piece = board[from];
            if (!piece || piece->GetColor() != aiColor) continue;
            if(piece->updateAllValidMoves(board) != 0) anyMoves = true;
        }
    }

    for (char file = 'a'; file <= 'h'; ++file) {
        for (char rank = '1'; rank <= '8'; ++rank) {
            std::string from = {file, rank};
            Piece* piece = board[from];
            if (!piece || piece->GetColor() != aiColor) continue;

            for (const auto& move : piece->ValidMovesAtPosition) {

                std::string to = move.first;
                Action action = move.second;

                board.UpdateBoard(from, to, action);

                int value = alphaBeta(board, maxDepth_ - 1, alpha, beta, false, aiColor);

                board.UndoMove();

                if (value > bestValue || !bestMove.first.empty()) {
                    bestValue = value;
                    bestMove = {from, to};
                }

                alpha = std::max(alpha, bestValue);
                if (beta <= alpha) break;
            }
            if (beta <= alpha) break;
        }
        if (beta <= alpha) break;
    }

    return anyMoves ? bestMove : std::make_pair("", "");
}

int AlphaBetaPruner::alphaBeta(ChessBoard board, int depth, int alpha, int beta, bool maximizing, PieceColor aiColor) {
    PieceColor currentColor = maximizing ? aiColor : getOppositeColor(aiColor);
    int bestValue = maximizing ? INT_MIN : INT_MAX;
    bool anyMoves = false;
        for (char file = 'a'; file <= 'h'; ++file) {
            for (char rank = '1'; rank <= '8'; ++rank) {
                std::string from = {file, rank};
                Piece* piece = board[from];
                if (!piece || piece->GetColor() != currentColor) continue;
                if(piece->updateAllValidMoves(board) != 0) anyMoves = true;
            }
        }

    if (depth == 0 || !anyMoves) {
        return evaluateBoard(board, aiColor, anyMoves);
    }   

    for (char file = 'a'; file <= 'h'; ++file) {
        for (char rank = '1'; rank <= '8'; ++rank) {
            std::string from = {file, rank};
            Piece* piece = board[from];
            if (!piece || piece->GetColor() != currentColor) continue;

            for (const auto& move : piece->ValidMovesAtPosition) {
                std::string to = move.first;
                Action action = move.second;

                board.UpdateBoard(from, to, action);

                int value = alphaBeta(board, maxDepth_ - 1, alpha, beta, !maximizing, aiColor);

                board.UndoMove();


                if (maximizing) {
                    bestValue = std::max(bestValue, value);
                    alpha = std::max(alpha, bestValue);
                } else {
                    bestValue = std::min(bestValue, value);
                    beta = std::min(beta, bestValue);
                }

                if (beta <= alpha) break;
            }
            if (beta <= alpha) break;
        }
        if (beta <= alpha) break;
    }

    return bestValue;
}

int AlphaBetaPruner::evaluateBoard(ChessBoard board, PieceColor aiColor, bool anyMoves) {
    if (!anyMoves) {
        if (board.IsCheckedSquare(board.WhiteKingPosition, Black)) {
            return aiColor == Black ? 20000 : -20000;
        }
        if (board.IsCheckedSquare(board.BlackKingPosition, White)) {
            return aiColor == White ? 20000 : -20000;
        }
        return 0;
    }

    int score = 0;
    for (char f = 'a'; f <= 'h'; ++f) {
        for (char r = '1'; r <= '8'; ++r) {
            Piece* p = board[{f, r}];
            if (p) {
                int val = getPieceValue(p->GetKind());
                score += (p->GetColor() == aiColor) ? val : -val;
            }
        }
    }
    return score;
}

int AlphaBetaPruner::getPieceValue(PieceKind kind) {
    switch (kind) {
    case pawn: return 100;
    case knight: return 320;
    case bishop: return 330;
    case rook: return 500;
    case queen: return 900;
    case king: return 20000;
    default: return 0;
    }
}

PieceColor AlphaBetaPruner::getOppositeColor(PieceColor color) {
    return (color == White) ? Black : White;
}
