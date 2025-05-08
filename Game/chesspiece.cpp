#include "chesspiece.h"
#include "mainwindow.h"
#include "promotion.h"
#include "winer.h"

QPointF CurrentP;


ChessPiece::ChessPiece(const QPixmap &pixmap ,const bool type) : QGraphicsPixmapItem(pixmap)
    ,whitePlayer(type){
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

void ChessPiece::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsPixmapItem::mousePressEvent(event);
    CurrentP.setX(this->pos().x());
    CurrentP.setY(this->pos().y());
}

void ChessPiece::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsPixmapItem::mouseMoveEvent(event);
}

void ChessPiece::changeImage(const QPixmap &pix){
    setPixmap(pix) ;
}

void ChessPiece::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsPixmapItem::mouseReleaseEvent(event);

    int x1 = qRound(CurrentP.x() / OneStep);
    int y1 = qRound(CurrentP.y() / OneStep);
    int x2 = qRound(pos().x() / OneStep);
    int y2 = qRound(pos().y() / OneStep);

    qreal newX = x2 * OneStep + 5;
    qreal newY = y2 * OneStep;

    if(x2 > 7 || x2 < 0 || y2 > 7 || y2 < 0) {
        changePiecePos(this->pos(), CurrentP, this);
        return;
    }

    std::string from = GetPos1(x1, (7 - y1));
    std::string to = GetPos1(x2, (7 - y2));
    Action action = invalidMove;
    GameState state = KeepPlying;

    if(LogicalGame->ApplayMove(from, to, action, state)) {
        grid[y1][x1] = nullptr;

        if(action == Capture || action == EnPassent) {
            int capturedY = y2;
            if(action == EnPassent) {
                capturedY = (y2 == 2) ? 3 : 4;
            }

            if(grid[capturedY][x2] != nullptr) {
                scene()->removeItem(grid[capturedY][x2]);
                delete grid[capturedY][x2];
                grid[capturedY][x2] = nullptr;
            }
        }
        switch(action) {
        case Move:
        case Capture:
            changePiecePos(this->pos(), QPointF(newX, newY), this);
            grid[y2][x2] = this;
            break;

        case LongCastle:
            changePiecePos(this->pos(), QPointF(2 * OneStep + 5, newY), this);
            changePiecePos(grid[y2][0]->pos(), QPointF(3 * OneStep + 5, newY), grid[y2][0]);
            grid[y2][2] = this;
            grid[y2][3] = grid[y2][0];
            grid[y2][0] = nullptr;
            break;

        case ShortCastle:
            changePiecePos(this->pos(), QPointF(6 * OneStep + 5, newY), this);
            changePiecePos(grid[y2][7]->pos(), QPointF(5 * OneStep + 5, newY), grid[y2][7]);
            grid[y2][6] = this;
            grid[y2][5] = grid[y2][7];
            grid[y2][7] = nullptr;
            break;

        case EnPassent:
            changePiecePos(this->pos(), QPointF(newX, newY), this);
            grid[y2][x2] = this;
            break;
        default:
            changePiecePos(this->pos(), CurrentP, this);
            break;
        }

        if(state == Promote){
            Promotion prom(nullptr, grid[y2][x2]);
            prom.exec();
            while(prom.promoteTo == '0');
            std::string temp = " ";
            temp[0] = prom.promoteTo;
            LogicalGame->ApplayMove(to, temp, action, state);
        }
        changePlayer();

        if(state == CheckMate) {
            QString winner = currentPlayer ? "Black wins by checkmate!" : "White wins by checkmate!";
            Winer *winnerDialog = new Winer(winner, qobject_cast<QWidget*>(this->scene()->parent()));
            winnerDialog->exec();
        }
        else if(state == StaleMate) {
            Winer *winnerDialog = new Winer("Game drawn by stalemate!", qobject_cast<QWidget*>(this->scene()->parent()));
            winnerDialog->exec();
        }

        else{
            std::pair<std::string, std::string> result = GameAi->findBestMove(*LogicalBoard, Black);
            int x1 = result.first[0] - 'a';
            int y1 = 7 - result.first[1] - '1';
            int x2 = result.second[0] - 'a';
            int y2 = 7 - result.second[1] - '1';

            qreal newX = x2 * OneStep + 5;
            qreal newY = y2 * OneStep;

            qreal OldX = x1 * OneStep + 5;
            qreal OldY = y1 * OneStep;

            if(x2 > 7 || x2 < 0 || y2 > 7 || y2 < 0) {
                changePiecePos(this->pos(), CurrentP, this);
                return;
            }

            std::string from = result.first;
            std::string to = result.second;
            Action action = invalidMove;
            GameState state = KeepPlying;

            if(LogicalGame->ApplayMove(from, to, action, state)) {
                ChessPiece* current = grid[y1][x1];
                grid[y1][x1] = nullptr;

                if(action == Capture || action == EnPassent) {
                    int capturedY = y2;
                    if(action == EnPassent) {
                        capturedY = (y2 == 2) ? 3 : 4;
                    }

                    if(grid[capturedY][x2] != nullptr) {
                        scene()->removeItem(grid[capturedY][x2]);
                        delete grid[capturedY][x2];
                        grid[capturedY][x2] = nullptr;
                    }
                }
                switch(action) {
                case Move:
                case Capture:
                    changePiecePos(QPointF(OldX, OldY), QPointF(newX, newY), current);
                    grid[y2][x2] = current;
                    break;

                case LongCastle:
                    changePiecePos(QPointF(OldX, OldY), QPointF(2 * OneStep + 5, newY), current);
                    changePiecePos(grid[y2][0]->pos(), QPointF(3 * OneStep + 5, newY), grid[y2][0]);
                    grid[y2][2] = current;
                    grid[y2][3] = grid[y2][0];
                    grid[y2][0] = nullptr;
                    break;

                case ShortCastle:
                    changePiecePos(QPointF(OldX, OldY), QPointF(6 * OneStep + 5, newY), current);
                    changePiecePos(grid[y2][7]->pos(), QPointF(5 * OneStep + 5, newY), grid[y2][7]);
                    grid[y2][6] = current;
                    grid[y2][5] = grid[y2][7];
                    grid[y2][7] = nullptr;
                    break;

                case EnPassent:
                    changePiecePos(QPointF(OldX, OldY), QPointF(newX, newY), current);
                    grid[y2][x2] = current;
                    break;
                default:
                    changePiecePos(QPointF(OldX, OldY), CurrentP, current);
                    break;
                }

                if(state == Promote){
                    Promotion prom(nullptr, grid[y2][x2]);
                    prom.exec();
                    while(prom.promoteTo == '0');
                    std::string temp = " ";
                    temp[0] = prom.promoteTo;
                    LogicalGame->ApplayMove(to, temp, action, state);
                }
                changePlayer();

                if(state == CheckMate) {
                    QString winner = currentPlayer ? "Black wins by checkmate!" : "White wins by checkmate!";
                    Winer *winnerDialog = new Winer(winner, qobject_cast<QWidget*>(this->scene()->parent()));
                    winnerDialog->exec();
                }
                else if(state == StaleMate) {
                    Winer *winnerDialog = new Winer("Game drawn by stalemate!", qobject_cast<QWidget*>(this->scene()->parent()));
                    winnerDialog->exec();
                }
        }
        }
    }
    else {
        changePiecePos(this->pos(), CurrentP, this);
    }
}


bool ChessPiece::playerType() const {
    return whitePlayer ;
}

void ChessPiece::enableMovement(){
    setFlag(QGraphicsItem::ItemIsMovable, true);
}

void ChessPiece::disableMovement(){
    setFlag(QGraphicsItem::ItemIsMovable, false);
}



ChessPieceWrapper::ChessPieceWrapper(ChessPiece* piece, QObject* parent)
    : QObject(parent), m_piece(piece)
{
}

QPointF ChessPieceWrapper::pos() const {
    return m_piece->pos();
}

void ChessPieceWrapper::setPos(const QPointF &position) {
    if (m_piece->pos() == position)
        return;
    m_piece->setPos(position);
    emit posChanged(position);
}


void changePiecePos(const QPointF &startPos, const QPointF &endPos, ChessPiece *ptr) {
    if (!ptr) return;

    ptr->setPos(startPos);

    ChessPieceWrapper *wrapper = new ChessPieceWrapper(ptr);

    QPropertyAnimation *animation = new QPropertyAnimation(wrapper, "pos");
    animation->setDuration(500);
    animation->setStartValue(startPos);
    animation->setEndValue(endPos);
    animation->setEasingCurve(QEasingCurve::InOutQuad);

    QObject::connect(animation, &QPropertyAnimation::finished, wrapper, &QObject::deleteLater);

    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
