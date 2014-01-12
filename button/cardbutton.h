#ifndef CARDBUTTON_H
#define CARDBUTTON_H
#include "picbutton.h"
#include "cardList.h"
#include <QLabel>
#include <QWidget>
class CardButton : public PicButton
{
private:
    CardList* cardList;
public:
    QLabel* label[5];
    bool isConnect;
    CardButton(int buttonKind,int paraX,int paraY,int paraW,int paraH,bool canBe,int cardNum,QWidget* parent);
    ~CardButton();
    void destroyLabel();
};

#endif // CARDBUTTON_H
