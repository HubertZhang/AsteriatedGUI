#ifndef CARDBUTTON_H
#define CARDBUTTON_H
#include "picbutton.h"
#include "cardList.h"
#include "placeinfo.h"
#include <QLabel>
#include <QWidget>
extern CardList cardlist;
class CardButton : public PicButton
{
    int card;
public:
    QLabel* label[5];
    explicit CardButton(int card, int paraX,int paraY, QWidget* parent);
};

#endif // CARDBUTTON_H
