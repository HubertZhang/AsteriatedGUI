#ifndef HAKUREIREIMU_H
#define HAKUREIREIMU_H

#include <QWidget>
#include "cardandskill.h"
#include "picbutton.h"
#include "newdialog.h"
#include "askdialog.h"

class window;
class HakureiReimu : public CardAndSkill
{
    Q_OBJECT
public:
    explicit HakureiReimu(PaintStruct* paintStruct,QWidget *parent,Window* showX);
    PicButton* magicGroup[2];
    PicButton* tokenPic;
    AskDialog* showFire;
    bool showFirePaint;
    bool ask;
    bool tokenPaint;
    NewDialog* dialog;
    CardButton* tokenButton[2];
    int token[2];
    int tokenNum;
    int elementCount;
    void paint(QPaintEvent *, QPainter *);
    void changeSelfMode(int mode);
    void setFrame();
    void skillCancel();
    void dialogSet(bool canX[10]);
    void dialogReset();
    void selfReset();
    void sendMessageSelf();
    void storeStatus();
    void reStore();
    bool storeArray[100];
    void nightSet();
    int cardRecord;
    bool showRecord;
    //void skillReset();
signals:
public slots:
    void magicSetZero();
    void magicSetOne();
    void skillset();
    void skillClear();
    void elementPlus();
    void elementMinus();
    void tokenSet();
    void tokenReset();
    void fireChoose();
    void fireNotChoose();
    void magicReset();
};

#endif // HAKUREIREIMU_H
