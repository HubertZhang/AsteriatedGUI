#ifndef ELEMENTMASTER_H
#define ELEMENTMASTER_H

#include <QWidget>
#include "cardandskill.h"
#include "picbutton.h"
class ElementMaster : public CardAndSkill
{
    Q_OBJECT
public:
    explicit ElementMaster(PaintStruct* paintStruct,QWidget *parent);
    PicButton* magicGroup[3];
    int magicCount;
    void paint(QPaintEvent *, QPainter *);
    void changeSelfMode(int mode);
    void skillCancel();
    //void skillReset();
signals:
public slots:
    void magicSetZero();
    void magicSetOne();
    void magicSetTwo();
    void skillset();
    void skillClear();
    void countPlus();
    void countMinus();
    void sendMessageSelf();
};
#endif // ELEMENTMASTER_H
