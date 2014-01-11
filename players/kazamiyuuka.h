#ifndef KAZAMIYUUKA_H
#define KAZAMIYUUKA_H

#include <QWidget>
#include "cardandskill.h"
#include "picbutton.h"
#include "newdialog.h"

class KazamiYuuka : public CardAndSkill
{
    Q_OBJECT
public:
    explicit KazamiYuuka(PaintStruct* paintStruct,QWidget *parent);
    NewDialog* dialog;
    bool ask;
    int YuukaTwoCount;
    //void paint(QPaintEvent *, QPainter *);
    void changeSelfMode(int mode);
    void setFrame();
    void skillCancel();
    void dialogSet(bool canX[10]);
    void dialogReset();
    void selfReset();
    void sendMessageSelf();
    void YuukaOne();
    void YuukaTwo();
    //void skillReset();
signals:
public slots:
    void YuukaTwoPlus();
    void YuukaTwoMinus();
};

#endif // KAZAMIYUUKA_H
