#include "winer.h"
#include "ui_winer.h"

Winer::Winer(QString winerName , QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Winer)
{
    ui->setupUi(this);
    QGraphicsScene *scene = new QGraphicsScene() ;
    ui->viewWiner->setScene(scene) ;
    resize(900 , 900) ;
    scene ->setSceneRect(0 , 0 , 700 , 700) ;
    QPixmap pix(":/Image/chees_images/queen-and-pawn-free-photo.jpg");

    QSize desiredSize(900, 900);
    QPixmap scaledPix = pix.scaled(desiredSize, Qt::IgnoreAspectRatio , Qt::SmoothTransformation);

    QGraphicsPixmapItem *pixItem = scene->addPixmap(scaledPix);
    pixItem->setPos((scene->width() - scaledPix.width()) / 2,(scene->height() - scaledPix.height())/ 2);

    QGraphicsTextItem *textItem = scene->addText(winerName);
    QFont bodoniFont("Bodoni MT", 28, QFont::Black, true);
    bodoniFont.setItalic(true);
    bodoniFont.setWeight(QFont::Black);
    textItem->setFont(bodoniFont);
    textItem->setPos(150, 50);
}

Winer::~Winer()
{
    delete ui;
}

