#ifndef ONLINEGAME_H
#define ONLINEGAME_H

#include "includesFile.h"

namespace Ui {
class onlineGame;
}

class onlineGame : public QDialog
{
    Q_OBJECT

public:
    explicit onlineGame(QWidget *parent = nullptr);
    ~onlineGame();

private slots:
    void on_cRoomBtn_clicked();

    void on_jRoomBtn_clicked();

    void on_goBackBtn_1_clicked();

    void on_goBackBtn_2_clicked();

    void on_submitBtn_clicked();

private:
    Ui::onlineGame *ui;
};

#endif // ONLINEGAME_H
