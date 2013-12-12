#ifndef ARBITRATIONMAID_H
#define ARBITRATIONMAID_H

#include <QWidget>
#include "cardandskill.h"
#include "picbutton.h"
class ArbitrationMaid : public CardAndSkill
{
    Q_OBJECT
public:
    explicit ArbitrationMaid(PaintStruct* paintStruct,QWidget *parent);
    PicButton* magicGroup[3];
    void paint(QPaintEvent *, QPainter *);
    void changeSelfMode(int mode);
    void skillCancel();
    void sendMessageSelf();
    void arbitrationEnd();
    //void skillReset();
signals:
public slots:
    void magicSetZero();
    void magicSetOne();
    void magicSetTwo();
    void skillset();
    void skillClear();
};
#endif // ARBITRATIONMAID_H
