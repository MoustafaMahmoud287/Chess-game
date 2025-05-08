#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "chesspiece.h"

extern ChessBoard* LogicalBoard;

extern std::vector<std::vector<ChessPiece*>> grid ;


class IntroWindow;
class TimerDisplay ;


extern TimerDisplay *blackTimer ;
extern TimerDisplay *whiteTimer ;

void changePlayer() ;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void setupGame(bool type) ;
    ~MainWindow();

private slots:
    void on_resetButtom_clicked();

    void on_backButton_clicked();

    void on_exit_Buttom_clicked();

    void on_resignButton_clicked();

    void on_drawButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene*scene;
    void setupBoard() ;
    void setupPieces();
    void setItem(QString path , int col , int row , const bool type) ;
};


class TimerDisplay : public QObject{
    Q_OBJECT
private:
    QTimer *timer ;
    QLCDNumber *lcdDisplayer ;
    QSlider *slider ;
    int timeLeft ;

private slots:
    void updateTimer();

public:
    TimerDisplay(QLCDNumber *lcd ,QSlider *slid , MainWindow *parent = nullptr) ;
    void stopTimer() ;
    void ContinueTimer() ;
    void restartTime();

};

#endif // MAINWINDOW_H
