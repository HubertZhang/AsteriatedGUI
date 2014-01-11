#ifndef MAGICMAID_H
#define MAGICMAID_H

#include <QWidget>
#include "cardandskill.h"
#include "picbutton.h"
#include "newdialog.h"
class MagicMaid : public CardAndSkill
{
    Q_OBJECT
public:
    explicit MagicMaid(PaintStruct* paintStruct,QWidget *parent);
    PicButton* magicGroup[3];
    //NewDialog* dialog;
    int stormCount;
    //bool ask;
    //void paint(QPaintEvent *, QPainter *);
    void changeSelfMode(int mode);
    void skillCancel();
    void sendMessageSelf();
    //void dialogSet(bool canX[10]);
    //void dialogReset();
    //void selfReset();
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
};
#endif // MAGICMAID_H
