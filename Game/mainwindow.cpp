#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include "introwindow.h"

std::vector<std::vector<ChessPiece*>> grid ;

ChessBoard* LogicalBoard = nullptr;
Game* LogicalGame = nullptr;
AlphaBetaPruner* GameAi;

TimerDisplay *blackTimer = nullptr ;
TimerDisplay *whiteTimer = nullptr ;

QLabel *ImageDisplay = nullptr ;
QLabel *PlayerName = nullptr;

QPixmap *whitePix = nullptr ;
QPixmap *blackPix = nullptr ;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) ,scene(new QGraphicsScene(this))
{
    player_Type pty(this) ;
    pty.exec() ;
    LogicalBoard = new ChessBoard(STANDARD_BOARD);
    LogicalGame = new Game(*LogicalBoard);
    GameAi = new AlphaBetaPruner(2);
    grid.resize(8);
    for(int i = 0 ; i  < 8  ; i++) grid[i].resize(8, nullptr) ;
    ui->setupUi(this);
    ui->view->setScene(scene) ;
    scene ->setSceneRect(0 , 0 , 700 , 700) ;

    setupBoard() ;
    setupPieces();

    blackTimer = new TimerDisplay(ui->BlackTimer , ui->BlackSlider , this) ;
    blackTimer->stopTimer() ;

    whiteTimer = new TimerDisplay(ui->WhiteTimer , ui->WhiteSlider , this) ;
    whiteTimer->stopTimer() ;

    if(currentPlayer == BlackPlayer) std::swap(blackTimer , whiteTimer) ;

    PlayerName = ui->displayName ;
    ImageDisplay = ui->ImageBox ;

    whitePix = new QPixmap(":/Image/chees_images/R (1).jpeg") ;
    *whitePix = whitePix->scaled(ui->ImageBox->size() ,Qt::IgnoreAspectRatio , Qt::SmoothTransformation);

    blackPix = new QPixmap(":/Image/chees_images/R.jpeg") ;
    *blackPix = blackPix->scaled(ui->ImageBox->size() ,Qt::IgnoreAspectRatio , Qt::SmoothTransformation);
    currentPlayer = !currentPlayer ;
    changePlayer() ;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupBoard() {
    bool isWhite = currentPlayer ;
    QColor color ;
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            color = isWhite ? QColor(234 , 233 , 212) : QColor(75 , 114 , 153);
            isWhite = !isWhite;

            scene->addRect(col * OneStep, row * OneStep, OneStep,OneStep, QPen(Qt::black), QBrush(color));
        }
        isWhite = !isWhite;
    }
}


void MainWindow::setItem(QString path , int col , int row , const bool type){
    ChessPiece *item = new ChessPiece(QPixmap(path) , type);
    item->setPos(col * OneStep + 5 , row * OneStep );
    item->setScale(0.9);
    scene->addItem(item);
    grid[row][col] = item ;
}

void MainWindow::setupPieces(){

    int posWhite{} , posBlack{};

    for (int col = 0; col < 8; col++) {
        posWhite = currentPlayer == WhitePlayer ? 6 : 1 ;
        setItem(":/Image/chees_images/pawn_white.png" , col , posWhite , WhitePlayer) ;
    }

    for (int col = 0; col < 8; col++) {
        posBlack = currentPlayer == BlackPlayer ? 6 : 1 ;
        setItem(":/Image/chees_images/pawn_black.png" , col , posBlack , BlackPlayer) ;
    }

    posWhite = currentPlayer == WhitePlayer ? 7 : 0 ;
    posBlack = currentPlayer == BlackPlayer ? 7 : 0 ;

    setItem(":/Image/chees_images/rook_white.png" , 0  , posWhite , WhitePlayer) ;
    setItem(":/Image/chees_images/rook_white.png" , 7  , posWhite , WhitePlayer) ;

    setItem(":/Image/chees_images/knight_white.png" , 1, posWhite , WhitePlayer) ;
    setItem(":/Image/chees_images/knight_white.png" , 6, posWhite , WhitePlayer) ;

    setItem(":/Image/chees_images/bishop_white.png" , 2, posWhite , WhitePlayer) ;
    setItem(":/Image/chees_images/bishop_white.png" , 5, posWhite , WhitePlayer) ;

    setItem(":/Image/chees_images/king_white.png" , 4 , posWhite , WhitePlayer) ;

    setItem(":/Image/chees_images/queen_white.png" , 3  , posWhite , WhitePlayer) ;


    setItem(":/Image/chees_images/rook_black.png" , 0  , posBlack  , BlackPlayer) ;
    setItem(":/Image/chees_images/rook_black.png" , 7  , posBlack  , BlackPlayer) ;


    setItem(":/Image/chees_images/knight_black.png" , 1, posBlack  , BlackPlayer) ;
    setItem(":/Image/chees_images/knight_black.png" , 6, posBlack  , BlackPlayer) ;



    setItem(":/Image/chees_images/bishop_black.png" , 2, posBlack  , BlackPlayer) ;
    setItem(":/Image/chees_images/bishop_black.png" , 5, posBlack  , BlackPlayer) ;


    setItem(":/Image/chees_images/king_black.png" , 4 , posBlack , BlackPlayer) ;


    setItem(":/Image/chees_images/queen_black.png" , 3  , posBlack , BlackPlayer) ;
}


void MainWindow::setupGame(bool type){
    if(isOnline){
        ui->resetButtom->deleteLater() ;
    }
    else{
        ui->buttonFram->deleteLater() ;
    }
}

void MainWindow::on_resetButtom_clicked()
{
    delete LogicalBoard;
    delete LogicalGame;
    LogicalBoard = nullptr;
    LogicalGame = nullptr;
    LogicalBoard = new ChessBoard(STANDARD_BOARD);
    LogicalGame = new Game(*LogicalBoard);
    currentPlayer = playerSelected ;
    setupBoard() ;
    setupPieces();
    whiteTimer->restartTime() ;
    blackTimer->restartTime() ;
    currentPlayer = !playerSelected ;
    changePlayer() ;
}


void MainWindow::on_backButton_clicked()
{
    IntroWindow * intro = new IntroWindow() ;
    intro->show() ;
    this->close() ;
}


void MainWindow::on_exit_Buttom_clicked()
{
    close() ;
}



void MainWindow::on_resignButton_clicked()
{

}


void MainWindow::on_drawButton_clicked()
{

}

void changePlayer(){

    if(currentPlayer == WhitePlayer)
    {
        whiteTimer->stopTimer() ;
    }
    else {
        blackTimer->stopTimer() ;
    }

    for(auto& arr : grid){
        for(auto& item : arr){
            if(item){
                if(item->playerType() == currentPlayer) item->disableMovement() ;
                else item->enableMovement() ;
            }
        }
    }

    currentPlayer = !currentPlayer ;
    if(currentPlayer == WhitePlayer) {
        whiteTimer->ContinueTimer();
        PlayerName->setText("White Player") ;
        PlayerName->setStyleSheet("color: white ; background-color: black ;") ;
        ImageDisplay->setPixmap(*whitePix) ;
    }
    else {
        blackTimer->ContinueTimer();
        PlayerName->setText("Black Player") ;
        PlayerName->setStyleSheet("color: black ; background-color: white ;") ;
        ImageDisplay->setPixmap(*blackPix) ;
    }
}





TimerDisplay::TimerDisplay(QLCDNumber *lcd ,QSlider *slid , MainWindow *parent) :
    lcdDisplayer(lcd) , slider(slid)
{
    timeLeft = GameTimer + 1 ;
    timer = new QTimer(parent) ;
    lcdDisplayer->setStyleSheet("background-color:rgb(234 , 233 , 212);") ;
    QPalette palette = lcdDisplayer->palette() ;
    palette.setColor(QPalette::WindowText , Qt::black) ;
    lcdDisplayer->setPalette(palette) ;
    lcdDisplayer->setSegmentStyle(QLCDNumber::Flat) ;

    connect(timer, &QTimer::timeout, this, &TimerDisplay::updateTimer);

    timer->start(1000) ;
    updateTimer() ;
}

void TimerDisplay::stopTimer(){
    timer->stop() ;
}

void TimerDisplay::updateTimer(){
    timeLeft-- ;
    slider->setValue(timeLeft) ;
    if (timeLeft == 0) {
        /*****************Action*************************/
        //////////////////////////////////////////////////
        //////////////////////////////////////////////////
        return;
    }
    int minutes = timeLeft / 60;
    int seconds = timeLeft % 60;
    QString timeText = QString("%1:%2").arg(minutes).arg(seconds, 2, 10, QLatin1Char('0'));
    lcdDisplayer->display(timeText) ;
}

void TimerDisplay::restartTime(){
    timer->stop() ;
    timeLeft = GameTimer ;
    slider->setValue(timeLeft) ;
    int minutes = timeLeft / 60;
    int seconds = timeLeft % 60;
    QString timeText = QString("%1:%2").arg(minutes).arg(seconds, 2, 10, QLatin1Char('0'));
    lcdDisplayer->display(timeText) ;
    timer->start(1000) ;
}

void TimerDisplay::ContinueTimer(){
    timer->start(1000) ;
}
