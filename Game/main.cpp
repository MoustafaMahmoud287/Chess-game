#include "introwindow.h"
#include "winer.h"
#include <QApplication>


IntroWindow *intro = nullptr ;

bool currentPlayer ;
bool playerSelected ;
bool isOnline = false ;
int roomID = -1 ;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    intro = new IntroWindow() ;
    intro->show() ;
    return a.exec();
}
