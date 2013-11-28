#ifndef PUREMAID_H
#define PUREMAID_H

#include <QWidget>
#include "cardandskill.h"
#include "picbutton.h"
#include "newdialog.h"
#include "framelabel.h"
class PureMaid : public CardAndSkill
{
    Q_OBJECT
public:
    explicit PureMaid(PaintStruct* paintStruct,QWidget *parent);
    NewDialog* dialog;
    PicButton* magicGroup[3];
    bool ask;
    int pureCureCount;
    void paint(QPaintEvent *, QPainter *);
    void changeSelfMode(int mode);
    void setFrame();
    void skillCancel();
    int pureLightCount;
    FrameLabel* pureCureFrame;
    bool frame;
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
    void pureCurePlus();
};

#endif // PUREMAID_H
