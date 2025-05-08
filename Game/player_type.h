#ifndef PLAYER_TYPE_H
#define PLAYER_TYPE_H

#include "includesFile.h"

namespace Ui {
class player_Type;
}

class player_Type : public QDialog
{
    Q_OBJECT

public:
    explicit player_Type(QWidget *parent = nullptr);
    ~player_Type();

private slots:
    void on_blackButton_clicked();

    void on_whiteButton_clicked();

private:
    Ui::player_Type *ui;
};

#endif // PLAYER_TYPE_H
