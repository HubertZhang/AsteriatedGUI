#ifndef HOSHIGUMAYUGI_H
#define HOSHIGUMAYUGI_H

#include <QWidget>
#include "cardandskill.h"
#include "picbutton.h"
#include "newdialog.h"
class HoshigumaYugi : public CardAndSkill
{
    Q_OBJECT
public:
    explicit HoshigumaYugi(PaintStruct* paintStruct,QWidget *parent);
    PicButton* provoke;
    NewDialog* dialog;
    bool ask;
    void paint(QPaintEvent *, QPainter *);
    void changeSelfMode(int mode);
    void setFrame();
    void skillCancel();
    void dialogSet(bool canX[10]);
    void dialogReset();
    void selfReset();
    void sendMessageSelf();
    void discardAll();
    //void skillReset();
signals:
public slots:
    void magicSetZero();
    void skillset();
    void skillClear();
};


#endif // HOSHIGUMAYUGI_H
