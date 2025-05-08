#include "../include/ChessPieces.h"
#include "../include/ChessBoard.h"

Queen::Queen(PieceColor c, std::string p) : Piece(c, p), VirtualRook(c, p), VirtualBishop(c, p) {
    /*
     * the queen is treated as rook and bishop at the same time
     */
    Kind = queen;
    PieceVal = 9;
}

Queen::~Queen() {}
 

Action Queen::IsValidMove(std::string& move, ChessBoard& Board) {

    if (move == pos) return invalidMove;
    Action result = VirtualRook.IsValidMove(move, Board); // test if the positon achivable by the rook
    if(result == invalidMove) result = VirtualBishop.IsValidMove(move, Board); // if it invalid with the rook test it with the bishop
    return result;

}

int Queen::updateAllValidMoves(ChessBoard& Board) {

    ValidMovesAtPosition.clear(); // clear the the moves from the previous move
    VirtualBishop.updateAllValidMoves(Board); // gets all possible moves form the bishop
    VirtualRook.updateAllValidMoves(Board); // gets all the possible moves from the rook

    ValidMovesAtPosition.reserve(VirtualBishop.ValidMovesAtPosition.size() + VirtualRook.ValidMovesAtPosition.size());
    /*
     *  merge the possible moves from the rook and bishop no need to find the rpeated moves between them
     because there is no intersection between the way rook and bishop move
     *
     */
    ValidMovesAtPosition.reserve(VirtualBishop.ValidMovesAtPosition.size() + VirtualRook.ValidMovesAtPosition.size());
    ValidMovesAtPosition.insert(ValidMovesAtPosition.end(), VirtualRook.ValidMovesAtPosition.begin(), VirtualRook.ValidMovesAtPosition.end());
    ValidMovesAtPosition.insert(ValidMovesAtPosition.end(), VirtualBishop.ValidMovesAtPosition.begin(), VirtualBishop.ValidMovesAtPosition.end());

    return (int)ValidMovesAtPosition.size(); // get all valid moves from the queen
}
