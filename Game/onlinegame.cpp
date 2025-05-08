#include "onlinegame.h"
#include "ui_onlinegame.h"

#include <QTabBar>
#include <QRandomGenerator>

onlineGame::onlineGame(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::onlineGame)
{
    ui->setupUi(this);
    ui->tabWidget->tabBar()->setTabVisible(0 , false) ;
    ui->tabWidget->tabBar()->setTabVisible(1 , false) ;
    ui->tabWidget->tabBar()->setTabVisible(2 , false) ;
    ui->tabWidget->setCurrentIndex(0) ;
}

onlineGame::~onlineGame()
{
    delete ui;
}



void onlineGame::on_cRoomBtn_clicked()
{
    ui->tabWidget->setCurrentIndex(2) ;
    roomID = QRandomGenerator::global()->bounded(1 , 256) ;
    ui->setID->setNum(roomID) ;
}


void onlineGame::on_jRoomBtn_clicked()
{
    ui->tabWidget->setCurrentIndex(1) ;
}


void onlineGame::on_goBackBtn_1_clicked()
{
    ui->tabWidget->setCurrentIndex(0) ;
}


void onlineGame::on_goBackBtn_2_clicked()
{
    ui->tabWidget->setCurrentIndex(0) ;
}


void onlineGame::on_submitBtn_clicked()
{
    QString val = ui->getID->text() ;
    roomID = val.toInt() ;
}

