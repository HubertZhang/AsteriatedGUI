#ifndef CHOOSECHARACTER_H
#define CHOOSECHARACTER_H

#include <QWidget>
#include <QPixmap>
#include <QString>
#include "picbutton.h"
class ChooseCharacter : public QWidget
{
    Q_OBJECT
public:
    QPixmap* bg;
    PicButton* character[3];
    PicButton* ensure;
    PicButton* cancel;
    QPixmap* choose;
    explicit ChooseCharacter(int numOne,int numTwo,int numThree,QWidget *parent = 0);
    void paint(QPaintEvent* event,QPainter* painter);
signals:
public slots:
};

#endif // CHOOSECHARACTER_H
