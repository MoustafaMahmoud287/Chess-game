#include "promotion.h"
#include "ui_promotion.h"

Promotion::Promotion(QWidget *parent , ChessPiece *item)
    : QDialog(parent)
    , ui(new Ui::Promotion)
{
    promoteTo = '0';
    ui->setupUi(this);
    piece = item ;
    if(piece == nullptr) return ;
    if(piece->playerType() == WhitePlayer){
        ui->queenButton->setStyleSheet( "QPushButton {"
                                       "   border: none;"
                                       "   background-image: url(:/Image/chees_images/queen_white.png);"
                                       "   background-repeat: no-repeat;"
                                       "   background-position: center;"
                                        "   min-height: 120px;"
                                       "}") ;
        ui->rookButton->setStyleSheet( "QPushButton {"
                                       "   border: none;"
                                       "   background-image: url(:/Image/chees_images/rook_white.png);"
                                       "   background-repeat: no-repeat;"
                                       "   background-position: center;"
                                        "   min-height: 120px;"
                                       "}") ;
        ui->knightButton->setStyleSheet( "QPushButton {"
                                       "   border: none;"
                                       "   background-image: url(:/Image/chees_images/knight_white.png);"
                                       "   background-repeat: no-repeat;"
                                       "   background-position: center;"
                                        "   min-height: 120px;"
                                       "}") ;
        ui->bishopButton->setStyleSheet( "QPushButton {"
                                       "   border: none;"
                                       "   background-image: url(:/Image/chees_images/bishop_white.png);"
                                       "   background-repeat: no-repeat;"
                                       "   background-position: center;"
                                       "   min-height: 120px;"
                                       "}") ;
    }
    else{
        ui->queenButton->setStyleSheet( "QPushButton {"
                                       "   border: none;"
                                       "   background-image: url(:/Image/chees_images/queen_black.png);"
                                       "   background-repeat: no-repeat;"
                                       "   background-position: center;"
                                       "   min-height: 120px;"
                                       "}") ;
        ui->rookButton->setStyleSheet( "QPushButton {"
                                      "   border: none;"
                                      "   background-image: url(:/Image/chees_images/rook_black.png);"
                                      "   background-repeat: no-repeat;"
                                      "   background-position: center;"
                                      "   min-height: 120px;"
                                      "}") ;
        ui->knightButton->setStyleSheet( "QPushButton {"
                                        "   border: none;"
                                        "   background-image: url(:/Image/chees_images/knight_black.png);"
                                        "   background-repeat: no-repeat;"
                                        "   background-position: center;"
                                        "   min-height: 120px;"
                                        "}") ;
        ui->bishopButton->setStyleSheet( "QPushButton {"
                                        "   border: none;"
                                        "   background-image: url(:/Image/chees_images/bishop_black.png);"
                                        "   background-repeat: no-repeat;"
                                        "   background-position: center;"
                                        "   min-height: 120px;"
                                        "}") ;
    }
}

Promotion::~Promotion()
{
    delete ui;
}

void Promotion::on_queenButton_clicked()
{
    promoteTo = 'q';
    if(piece == nullptr) return ;
    if( piece->playerType() == WhitePlayer ){
        piece->changeImage(QPixmap(":/Image/chees_images/queen_white.png")) ;
    }
    else{
        piece->changeImage(QPixmap(":/Image/chees_images/queen_black.png")) ;
    }
    this->close() ;
}


void Promotion::on_rookButton_clicked()
{
    promoteTo = 'r';
    if(piece == nullptr) return ;
    if( piece->playerType() == WhitePlayer ){
        piece->changeImage(QPixmap(":/Image/chees_images/rook_white.png")) ;
    }
    else{
        piece->changeImage(QPixmap(":/Image/chees_images/rook_black.png")) ;
    }
    this->close() ;
}


void Promotion::on_bishopButton_clicked()
{
    promoteTo = 'b';
    if(piece == nullptr) return ;
    if( piece->playerType() == WhitePlayer ){
        piece->changeImage(QPixmap(":/Image/chees_images/bishop_white.png")) ;
    }
    else{
        piece->changeImage(QPixmap(":/Image/chees_images/bishop_black.png")) ;
    }
    this->close();
}


void Promotion::on_knightButton_clicked()
{
    promoteTo = 'k';
    if(piece == nullptr) return ;
    if( piece->playerType() == WhitePlayer ){
        piece->changeImage(QPixmap(":/Image/chees_images/knight_white.png")) ;
    }
    else{
        piece->changeImage(QPixmap(":/Image/chees_images/knight_black.png")) ;
    }
    this->close() ;
}
