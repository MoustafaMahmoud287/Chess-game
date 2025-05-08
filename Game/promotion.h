#ifndef PROMOTION_H
#define PROMOTION_H

#include "chesspiece.h"

namespace Ui {
class Promotion;
}

class Promotion : public QDialog
{
    Q_OBJECT

public:
    explicit Promotion(QWidget *parent = nullptr , ChessPiece *item = nullptr);
    char promoteTo;
    ~Promotion();

private slots:
    void on_queenButton_clicked();

    void on_rookButton_clicked();

    void on_bishopButton_clicked();

    void on_knightButton_clicked();

private:
    Ui::Promotion *ui;
    ChessPiece *piece;
};

#endif // PROMOTION_H
