#ifndef DARKKILLER_H
#define DARKKILLER_H

#include <QWidget>
#include "cardandskill.h"
#include "picbutton.h"
#include "newdialog.h"

class DarkKiller : public CardAndSkill
{
    Q_OBJECT
public:
    explicit DarkKiller(PaintStruct* paintStruct,QWidget *parent);
    NewDialog* dialog;
    bool ask;
    int waterCount;
    void paint(QPaintEvent *, QPainter *);
    void changeSelfMode(int mode);
    void dialogSet(bool canX[10]);
    void dialogReset();
    void setFrame();
    void selfReset();
    void skillCancel();
    void sendMessageSelf();
    //void skillReset();
signals:

public slots:
    void countPlus();
    void countMinus();
};

#endif // DARKKILLER_H
