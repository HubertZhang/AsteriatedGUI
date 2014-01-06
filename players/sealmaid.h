#ifndef SEALMAID_H
#define SEALMAID_H

#include <QWidget>
#include "cardandskill.h"
#include "picbutton.h"
#include "newdialog.h"
class SealMaid : public CardAndSkill
{
    Q_OBJECT
public:
    explicit SealMaid(PaintStruct* paintStruct,QWidget *parent);
    NewDialog* dialog;
    NewDialog* sealBreak;
    PicButton* magicGroup[3];
    bool ask;
    bool reminiscence;
    void paint(QPaintEvent *, QPainter *);
    void changeSelfMode(int mode);
    void dialogSet(bool canX[10]);
    void dialogReset();
    void setFrame();
    void selfReset();
    void skillCancel();
    int getCardName(int);
    void sendMessageSelf();
    //void skillReset();
signals:
public slots:
    void skillset();
    void magicSetZero();
    void magicSetOne();
    void magicSetTwo();
    void skillClear();
    void reminiscenceSet();
    void reminiscenceReset();
};
#endif // SEALMAID_H
