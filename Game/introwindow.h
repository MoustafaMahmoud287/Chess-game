#ifndef INTROWINDOW_H
#define INTROWINDOW_H

#include "mainwindow.h"

namespace Ui {
class IntroWindow;
}

class IntroWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow *window ;
    explicit IntroWindow(QWidget *parent = nullptr);
    ~IntroWindow();

private slots:
    void on_offlineButton_clicked();

    void on_onlineButton_clicked();

    void on_quitButton_clicked();

private:
    Ui::IntroWindow *ui;
};

#endif // INTROWINDOW_H
