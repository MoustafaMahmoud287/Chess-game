#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include "includesFile.h"
#include "include/ChessBoard.h"
#include "include/ChessGame.h"
#include "include/AlphaBetaPruner.h"
#include "player_type.h"

extern ChessBoard* LogicalBoard;
extern Game* LogicalGame;
extern AlphaBetaPruner* GameAi;

class ChessPiece : public QGraphicsPixmapItem {
public:
    ChessPiece(const QPixmap &pixmap ,const bool type) ;
    bool playerType() const ;
    void enableMovement() ;
    void disableMovement() ;
    void changeImage(const QPixmap &pix) ;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override ;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override ;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override ;
private:
    bool whitePlayer ;
};


class ChessPieceWrapper : public QObject {
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos NOTIFY posChanged)
public:
    explicit ChessPieceWrapper(ChessPiece* piece, QObject* parent = nullptr);

    QPointF pos() const;

    void setPos(const QPointF &position);

signals:
    void posChanged(const QPointF &newPos);

private:
    ChessPiece* m_piece;
};



void changePiecePos(const QPointF &startPos, const QPointF &endPos, ChessPiece *ptr) ;

#endif // CHESSPIECE_H
