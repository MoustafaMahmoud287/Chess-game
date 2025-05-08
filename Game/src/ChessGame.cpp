#include "../include/ChessGame.h"
#include "../include/ChessBoard.h"
#include "../include/ChessPieces.h"

Game::Game(ChessBoard& B) : Board(B){
	PlayerTurn = White;
	MoveNumber = 0;
	AllValidMovesAtPostionCounnter = 0;
	GetGameState();
}

void Game::GetGameState(){
	AllValidMovesAtPostionCounnter = 0;
    std::string InitialPositon = "a0";
    for (char file = 'a'; file <= 'h'; file++) {
        InitialPositon[0] = file;
        for (int rank = '1'; rank <= '8'; rank++) {
            InitialPositon[1] = rank;
			if (Board[InitialPositon] != nullptr && Board[InitialPositon]->GetColor() == PlayerTurn) {
				AllValidMovesAtPostionCounnter += Board[InitialPositon]->updateAllValidMoves(Board);
			}
		}
	}

	if (AllValidMovesAtPostionCounnter == 0) {

		std::string KingPosition = (PlayerTurn == White) ? Board.WhiteKingPosition : Board.BlackKingPosition;
		PieceColor Attacker = (PlayerTurn == White) ? Black : White;
		bool IsCheked = Board.IsCheckedSquare(KingPosition, Attacker);

		if (IsCheked) state = CheckMate;
		else state = StaleMate;
	}
	else state = KeepPlying;
}

void Game::ChangePlayingSide(){
	PlayerTurn = (PlayerTurn == White) ? Black : White;
}

bool Game::IsAnyPromotion(){
    std::string position = "a1";

    for(int j = 0; j < 2; j++){
        for(char i = 'a'; i <= 'h'; i++){
            position[0] = i;
            if(Board[position] != nullptr && Board[position]->GetKind() == pawn) return true;
        }
        position[1] = '8';
    }

    return false;
}

bool Game::ApplayMove(std::string moveFrom , std::string moveTo, Action& action, GameState& CurrentState) {
    if(CurrentState == Promote){

        PieceColor color = Board[moveFrom]->GetColor();
        delete Board[moveFrom];
        Board[moveFrom] = nullptr;

        switch(moveTo[0]){
        case 'q':
            Board[moveFrom] = new Queen(color, moveFrom);
            break;
        case 'r':
            Board[moveFrom] = new Rook(color, moveFrom);
            break;
        case 'k':
            Board[moveFrom] = new Knight(color, moveFrom);
            break;
        case 'b':
            Board[moveFrom] = new Bishop(color, moveFrom);
            break;
        }
        ChangePlayingSide();
        GetGameState();
        CurrentState = state;
        return true;
    }

    else {
        action = invalidMove;
        if (Board[moveFrom] == nullptr || Board[moveFrom]->GetColor() != PlayerTurn) return false;
        int CountOfPieceMoves = (int)Board[moveFrom]->ValidMovesAtPosition.size();
        for (int i = 0; i < CountOfPieceMoves; i++) {
            if (Board[moveFrom]->ValidMovesAtPosition[i].first == moveTo) {
                action = Board[moveFrom]->ValidMovesAtPosition[i].second;
                Board.UpdateBoard(moveFrom, moveTo, action);
                if(IsAnyPromotion() == true){CurrentState = Promote; return true;}
                ChangePlayingSide();
                GetGameState();
                CurrentState = state;
                return true;
            }
        }
    }

	return false;
}
