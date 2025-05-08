#include "player_type.h"
#include "ui_player_type.h"

player_Type::player_Type(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::player_Type)
{
    ui->setupUi(this);
    ui->blackButton->setStyleSheet("QPushButton {"
                                   "   border: none;"
                                   "   background-repeat: no-repeat;"
                                   "   background-position: center;"
                                   "   min-height: 180px;"
                                   "}") ;

    QPixmap pix(":/Image/chees_images/R.jpeg");
    pix = pix.scaled(ui->blackButton->width() * 4, ui->blackButton->height() * 1.2,
                                   Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->blackButton->setIcon(pix);
    ui->blackButton->setIconSize(pix.size());

    ui->whiteButton->setStyleSheet("QPushButton {"
                                   "   border: none;"
                                   "   background-repeat: no-repeat;"
                                   "   background-position: center;"
                                   "   min-height: 180px;"
                                   "}") ;
    QPixmap pix2(":/Image/chees_images/R (1).jpeg") ;
    pix2 = pix2.scaled(ui->whiteButton->width() * 4 , ui->whiteButton->height() * 1.2 ,
                       Qt::IgnoreAspectRatio , Qt::SmoothTransformation) ;
    ui->whiteButton->setIcon(pix2) ;
    ui->whiteButton->setIconSize(pix2.size()) ;

}

player_Type::~player_Type()
{
    delete ui;
}

void player_Type::on_blackButton_clicked()
{
    playerSelected = BlackPlayer ;
    currentPlayer = BlackPlayer ;
    this->close() ;
}


void player_Type::on_whiteButton_clicked()
{
    playerSelected = WhitePlayer ;
    currentPlayer = WhitePlayer ;
    this->close() ;
}

