#include "../include/ChessPieces.h"
#include "../include/ChessBoard.h"

ChessBoard::ChessBoard(InitialPositon TYPE) : ActualBoard(8, std::vector<Piece*>(8, nullptr)) {
    if (TYPE == STANDARD_BOARD) {
        // Initialize white pieces
        ActualBoard[0][0] = new Rook(White, "a1");
        ActualBoard[0][1] = new Knight(White, "b1");
        ActualBoard[0][2] = new Bishop(White, "c1");
        ActualBoard[0][3] = new Queen(White, "d1");
        ActualBoard[0][4] = new King(White, "e1");
        ActualBoard[0][5] = new Bishop(White, "f1");
        ActualBoard[0][6] = new Knight(White, "g1");
        ActualBoard[0][7] = new Rook(White, "h1");

        // Initialize pawns
        for (int i = 0; i < 8; i++) {
            ActualBoard[1][i] = new Pawn(White, GetSquare('a' + i, '2'));
            ActualBoard[6][i] = new Pawn(Black, GetSquare('a' + i, '7'));
        }

        // Initialize black pieces
        ActualBoard[7][0] = new Rook(Black, "a8");
        ActualBoard[7][1] = new Knight(Black, "b8");
        ActualBoard[7][2] = new Bishop(Black, "c8");
        ActualBoard[7][3] = new Queen(Black, "d8");
        ActualBoard[7][4] = new King(Black, "e8");
        ActualBoard[7][5] = new Bishop(Black, "f8");
        ActualBoard[7][6] = new Knight(Black, "g8");
        ActualBoard[7][7] = new Rook(Black, "h8");

        WhiteKingPosition = "e1";
        BlackKingPosition = "e8";
    }
}
ChessBoard::ChessBoard(ChessBoard& board): ActualBoard(8, std::vector<Piece*>(8, nullptr)) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if(board.ActualBoard[i][j]){
                switch (board.ActualBoard[i][j]->GetKind()){
                case queen: ActualBoard[i][j] = new Queen(board.ActualBoard[i][j]->GetColor(), board.ActualBoard[i][j]->GetPositon()); break;
                case pawn: ActualBoard[i][j] = new Pawn(board.ActualBoard[i][j]->GetColor(), board.ActualBoard[i][j]->GetPositon());
                    dynamic_cast<Pawn*>(ActualBoard[i][j])->MoveWithTwoSquares = dynamic_cast<Pawn*>(board.ActualBoard[i][j])->MoveWithTwoSquares;
                    break;
                case bishop: ActualBoard[i][j] = new Bishop(board.ActualBoard[i][j]->GetColor(), board.ActualBoard[i][j]->GetPositon()); break;
                case rook: ActualBoard[i][j] = new Rook(board.ActualBoard[i][j]->GetColor(), board.ActualBoard[i][j]->GetPositon());
                    dynamic_cast<Rook*>(ActualBoard[i][j])->MovedBefore = dynamic_cast<Rook*>(board.ActualBoard[i][j])->MovedBefore;
                    break;
                case knight: ActualBoard[i][j] = new Knight(board.ActualBoard[i][j]->GetColor(), board.ActualBoard[i][j]->GetPositon()); break;
                case king: ActualBoard[i][j] = new King(board.ActualBoard[i][j]->GetColor(), board.ActualBoard[i][j]->GetPositon());
                    dynamic_cast<King*>(ActualBoard[i][j])->MovedBefore = dynamic_cast<King*>(board.ActualBoard[i][j])->MovedBefore;
                    break;
                default: break;
                }
            }
            else ActualBoard[i][j] = nullptr;
        }
    }
    WhiteKingPosition = board.WhiteKingPosition;
    BlackKingPosition = board.BlackKingPosition;
    lastFrom = board.lastFrom;
    lastTo = board.lastTo;
    lastAction = board.lastAction;
    lastCaptured = board.lastCaptured;
}
ChessBoard::~ChessBoard() {
    for (auto& row : ActualBoard) {
        for (auto& piece : row) {
            delete piece;
            piece = nullptr;
        }
    }
}

Piece*& ChessBoard::operator[](std::string pos) {
    if (pos.length() != 2 || !isInBounds(pos[0], pos[1])) {
        throw std::out_of_range("Invalid board position: " + pos);
    }
    return ActualBoard[pos[1] - '1'][pos[0] - 'a'];
}

bool ChessBoard::checkedByPawn(std::string square, PieceColor attacker) {
    if (square.length() != 2) return false;

    char rank = square[1] + (attacker == Black ? 1 : -1);
    for (int dx : {-1, 1}) {
        char file = square[0] + dx;
        if (isInBounds(file, rank)) {
            std::string pos = GetSquare(file, rank);
            Piece* p = (*this)[pos];
            if (p && p->Kind == pawn && p->Color == attacker)
                return true;
        }
    }
    return false;
}

bool ChessBoard::checkedByBishopOrQueen(std::string square, PieceColor attacker) {
    if (square.length() != 2) return false;

    const int dirs[4][2] = {{1,1}, {1,-1}, {-1,1}, {-1,-1}};
    for (const auto& dir : dirs) {
        char file = square[0] + dir[0];
        char rank = square[1] + dir[1];
        while (isInBounds(file, rank)) {
            Piece* p = (*this)[GetSquare(file, rank)];
            if (p) {
                if ((p->Kind == bishop || p->Kind == queen) && p->Color == attacker)
                    return true;
                break;
            }
            file += dir[0];
            rank += dir[1];
        }
    }
    return false;
}

bool ChessBoard::checkedByRookOrQueen(std::string square, PieceColor attacker) {
    if (square.length() != 2) return false;

    const int dirs[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    for (const auto& dir : dirs) {
        char file = square[0] + dir[0];
        char rank = square[1] + dir[1];
        while (isInBounds(file, rank)) {
            Piece* p = (*this)[GetSquare(file, rank)];
            if (p) {
                if ((p->Kind == rook || p->Kind == queen) && p->Color == attacker)
                    return true;
                break;
            }
            file += dir[0];
            rank += dir[1];
        }
    }
    return false;
}

bool ChessBoard::checkedByKnight(std::string square, PieceColor attacker) {
    if (square.length() != 2) return false;

    const int dirs[8][2] = {{2,1}, {2,-1}, {-2,1}, {-2,-1}, {1,2}, {1,-2}, {-1,2}, {-1,-2}};
    for (const auto& dir : dirs) {
        char file = square[0] + dir[0];
        char rank = square[1] + dir[1];
        if (isInBounds(file, rank)) {
            Piece* p = (*this)[GetSquare(file, rank)];
            if (p && p->Kind == knight && p->Color == attacker)
                return true;
        }
    }
    return false;
}

bool ChessBoard::checkedByKing(std::string square, PieceColor attacker) {
    if (square.length() != 2) return false;

    const int dirs[8][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}, {1,1}, {1,-1}, {-1,1}, {-1,-1}};
    for (const auto& dir : dirs) {
        char file = square[0] + dir[0];
        char rank = square[1] + dir[1];
        if (isInBounds(file, rank)) {
            Piece* p = (*this)[GetSquare(file, rank)];
            if (p && p->Kind == king && p->Color == attacker)
                return true;
        }
    }
    return false;
}

bool ChessBoard::IsCheckedSquare(std::string square, PieceColor attacker) {
    if (square.length() != 2 || !isInBounds(square[0], square[1])) {
        return false;
    }
    return checkedByPawn(square, attacker)
           || checkedByBishopOrQueen(square, attacker)
           || checkedByRookOrQueen(square, attacker)
           || checkedByKnight(square, attacker)
           || checkedByKing(square, attacker);
}

bool ChessBoard::WouldBeInCheckAfterMove(std::string from, std::string to, PieceColor playerColor, bool isEnPassant) {
    if (from.length() != 2 || to.length() != 2 ||
        !isInBounds(from[0], from[1]) || !isInBounds(to[0], to[1])) {
        return false;
    }

    Piece* movedPiece = (*this)[from];
    if (!movedPiece) return false;

    Piece* capturedPiece = (*this)[to];
    Piece* enPassantCaptured = nullptr;

    // Make the move temporarily
    (*this)[to] = movedPiece;
    (*this)[from] = nullptr;
    std::string oldPos = movedPiece->pos;
    movedPiece->pos = to;

    std::string originalKingPos = (movedPiece->Kind == king) ? (playerColor == White ? WhiteKingPosition : BlackKingPosition) : "";

    // Update king position if moving the king
    if (movedPiece->Kind == king) {
        if (playerColor == White)
            WhiteKingPosition = to;
        else
            BlackKingPosition = to;
    }

    // Handle en passant capture
    if (isEnPassant) {
        std::string capturedSquare = GetSquare(to[0], from[1]);
        enPassantCaptured = (*this)[capturedSquare];
        (*this)[capturedSquare] = nullptr;
    }

    // Check if king is in check
    std::string kingPos = (playerColor == White) ? WhiteKingPosition : BlackKingPosition;
    bool inCheck = IsCheckedSquare(kingPos, (playerColor == White ? Black : White));

    // Undo the move
    movedPiece->pos = oldPos;
    (*this)[from] = movedPiece;
    (*this)[to] = capturedPiece;

    if (isEnPassant && enPassantCaptured) {
        std::string capturedSquare = GetSquare(to[0], from[1]);
        (*this)[capturedSquare] = enPassantCaptured;
    }

    if (movedPiece->Kind == king) {
        if (playerColor == White)
            WhiteKingPosition = originalKingPos;
        else
            BlackKingPosition = originalKingPos;
    }

    return inCheck;
}

void ChessBoard::UpdateBoard(std::string from, std::string to, Action action) {
    if (from.length() != 2 || to.length() != 2 ||
        !isInBounds(from[0], from[1]) || !isInBounds(to[0], to[1])) {
        return;
    }

    Piece* movingPiece = (*this)[from];
    if (!movingPiece) return;

    // Push current move information to stacks for undo
    lastFrom = from;
    lastTo = to;
    lastAction = action;
    lastCaptured = empty;
    // For captures, store what was captured (or invalidMove if nothing)
    if (action == Capture) {
        lastCaptured = (*this)[to] ? (*this)[to]->GetKind() : empty;
    }
    else if (action == EnPassent) {
        std::string capturedPos = GetSquare(to[0], from[1]);
        lastCaptured = (*this)[capturedPos] ? (*this)[capturedPos]->GetKind() : empty;
    }
    else {
        lastCaptured = empty;
    }

    switch (action) {
    case Move:
        (*this)[to] = movingPiece;
        (*this)[from] = nullptr;
        movingPiece->MoveTo(to);
        UpdateKingPosition(from, to);
        break;

    case Capture:
        delete (*this)[to];
        (*this)[to] = movingPiece;
        (*this)[from] = nullptr;
        movingPiece->MoveTo(to);
        UpdateKingPosition(from, to);
        break;

    case EnPassent: {
        std::string capturedPos = GetSquare(to[0], from[1]);
        delete (*this)[capturedPos];
        (*this)[capturedPos] = nullptr;
        (*this)[to] = movingPiece;
        (*this)[from] = nullptr;
        movingPiece->MoveTo(to);
        break;
    }

    case LongCastle: {
        std::string rookFrom = GetSquare('a', from[1]);
        std::string rookTo = GetSquare('d', from[1]);
        std::string kingTo = GetSquare('c', from[1]);

        (*this)[kingTo] = (*this)[from];
        (*this)[rookTo] = (*this)[rookFrom];
        (*this)[from] = nullptr;
        (*this)[rookFrom] = nullptr;

        (*this)[kingTo]->MoveTo(kingTo);
        (*this)[rookTo]->MoveTo(rookTo);
        UpdateKingPosition(from, kingTo);

        // Push additional info for castle undo
        lastFrom = rookFrom;
        lastTo = rookTo;
        lastAction = Move;  // Rook movement is treated as a regular move
        lastCaptured = empty;
        break;
    }

    case ShortCastle: {
        std::string rookFrom = GetSquare('h', from[1]);
        std::string rookTo = GetSquare('f', from[1]);
        std::string kingTo = GetSquare('g', from[1]);

        (*this)[kingTo] = (*this)[from];
        (*this)[rookTo] = (*this)[rookFrom];
        (*this)[from] = nullptr;
        (*this)[rookFrom] = nullptr;

        (*this)[kingTo]->MoveTo(kingTo);
        (*this)[rookTo]->MoveTo(rookTo);
        UpdateKingPosition(from, kingTo);

        // Push additional info for castle undo
        lastFrom = rookFrom;
        lastTo = rookTo;
        lastAction = Move;  // Rook movement is treated as a regular move
        lastCaptured = empty;
        break;
    }

    default:
        break;
    }
}

void ChessBoard::UndoMove() {

    Action action = lastAction;
    std::string from = lastFrom;
    std::string to = lastTo;
    PieceKind captured = lastCaptured;

    switch (action) {
    case Move: {
        Piece* movedPiece = (*this)[to];
        (*this)[from] = movedPiece;
        (*this)[to] = nullptr;
        movedPiece->MoveTo(from);
        UpdateKingPosition(to, from);
        break;
    }
    case Capture: {
        Piece* movedPiece = (*this)[to];
        (*this)[from] = movedPiece;
        movedPiece->MoveTo(from);

        // Restore captured piece if there was one
        if (captured != empty) {
            PieceColor capturedColor = movedPiece->Color == White ? Black : White;
            std::string pos = to;

            switch (captured) {
            case pawn:
                (*this)[to] = new Pawn(capturedColor, pos);
                break;
            case rook:
                (*this)[to] = new Rook(capturedColor, pos);
                break;
            case knight:
                (*this)[to] = new Knight(capturedColor, pos);
                break;
            case bishop:
                (*this)[to] = new Bishop(capturedColor, pos);
                break;
            case queen:
                (*this)[to] = new Queen(capturedColor, pos);
                break;
            case king:
                (*this)[to] = new King(capturedColor, pos);
                break;
            default:
                (*this)[to] = nullptr;
                break;
            }
        }

        else {
            (*this)[to] = nullptr;
        }
        UpdateKingPosition(to, from);
        break;
    }
    case EnPassent: {
        Piece* movedPawn = (*this)[to];
        (*this)[from] = movedPawn;
        movedPawn->MoveTo(from);
        (*this)[to] = nullptr;

        // Restore the captured pawn
        if (captured != empty) {
            std::string capturedPos = GetSquare(to[0], from[1]);
            (*this)[capturedPos] = new Pawn(movedPawn->Color == White ? Black : White, capturedPos);
            dynamic_cast<Pawn*>((*this)[capturedPos])->MoveWithTwoSquares = true;
        }
        break;
    }
    case LongCastle: {
        // Move king back
        std::string kingTo = GetSquare('c', from[1]);
        Piece* king = (*this)[kingTo];
        (*this)[from] = king;
        (*this)[kingTo] = nullptr;
        king->MoveTo(from);

        // Move rook back
        std::string rookTo = GetSquare('d', from[1]);
        std::string rookFrom = GetSquare('a', from[1]);
        Piece* rook = (*this)[rookTo];
        (*this)[rookFrom] = rook;
        (*this)[rookTo] = nullptr;
        rook->MoveTo(rookFrom);

        UpdateKingPosition(kingTo, from);
        break;
    }
    case ShortCastle: {
        // Move king back
        std::string kingTo = GetSquare('g', from[1]);
        Piece* king = (*this)[kingTo];
        (*this)[from] = king;
        (*this)[kingTo] = nullptr;
        king->MoveTo(from);

        // Move rook back
        std::string rookTo = GetSquare('f', from[1]);
        std::string rookFrom = GetSquare('h', from[1]);
        Piece* rook = (*this)[rookTo];
        (*this)[rookFrom] = rook;
        (*this)[rookTo] = nullptr;
        rook->MoveTo(rookFrom);

        UpdateKingPosition(kingTo, from);
        break;
    }
    default:
        break;
    }
}

void ChessBoard::UpdateKingPosition(const std::string& from, const std::string& to) {
    if (from == BlackKingPosition) {
        BlackKingPosition = to;
    } else if (from == WhiteKingPosition) {
        WhiteKingPosition = to;
    }
}
