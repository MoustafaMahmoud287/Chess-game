#include "introwindow.h"
#include "ui_introwindow.h"
#include "mainwindow.h"
#include "onlinegame.h"

IntroWindow::IntroWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::IntroWindow)
{
    ui->setupUi(this);
}

IntroWindow::~IntroWindow()
{
    delete ui;
}

void IntroWindow::on_offlineButton_clicked()
{
    isOnline = false ;
    window = new MainWindow() ;
    window ->show() ;
    window ->setupGame(isOnline) ;
    this ->close() ;
}


void IntroWindow::on_onlineButton_clicked()
{
    isOnline = true ;
    onlineGame game ;
    game.exec() ;

}


void IntroWindow::on_quitButton_clicked()
{
    this->close() ;
}

