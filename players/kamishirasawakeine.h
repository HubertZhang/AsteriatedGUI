#ifndef KAMISHIRASAWAKEINE_H
#define KAMISHIRASAWAKEINE_H

#include <QWidget>
#include "cardandskill.h"
#include "picbutton.h"
#include "newdialog.h"

class KamishirasawaKeine : public CardAndSkill
{
    Q_OBJECT
public:
    explicit KamishirasawaKeine(PaintStruct* paintStruct,QWidget *parent);
    PicButton* magicGroup[2];
    bool ask;
    NewDialog* dialog;
    void paint(QPaintEvent *, QPainter *);
    void changeSelfMode(int mode);
    void setFrame();
    void skillCancel();
    void dialogSet(bool canX[10]);
    void dialogReset();
    void selfReset();
    void sendMessageSelf();
    int magicRespondCount;
    int magicCodeCount;
    int sacredCodeCount;
    //void skillReset();
signals:
public slots:
    void magicSetZero();
    void magicSetOne();
    void skillset();
    void skillClear();
    void magicRespondPlus();
    void magicRespondMinus();
    void magicCodePlus();
    void magicCodeMinus();
    void sacredCodePlus();
    void sacredCodeMinus();
    void sacredCodeCharacterSet();
};

#endif // KAMISHIRASAWAKEINE_H
