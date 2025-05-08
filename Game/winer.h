#ifndef WINER_H
#define WINER_H

#include "includesFile.h"

namespace Ui {
class Winer;
}

class Winer : public QDialog
{
    Q_OBJECT

public:
    explicit Winer(QString winerName , QWidget *parent = nullptr);
    ~Winer();

private:
    Ui::Winer *ui;
};

#endif // WINER_H
