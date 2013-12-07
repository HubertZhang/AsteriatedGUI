#ifndef CARDANDSKILL_H
#define CARDANDSKILL_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include "cardbutton.h"
#include "paintstruct.h"
#include "cardList.h"
#include "card.h"
#include "framelabel.h"

class CardAndSkill : public QWidget
{
    Q_OBJECT
public:   
    PaintStruct* paintStructX;
    QWidget* windowX;
    CardList* cardList;
    FrameLabel* frameLabel;
    int paintMode;
    bool frame;
    bool cancelClick;
    CardButton* cardButton[15];
    PicButton* ensure;
    PicButton* cancel;
    int card[15];
    int cardNum;
    int informationKind;
    explicit CardAndSkill(PaintStruct* paintStruct,QWidget *parent);
    virtual void paint(QPaintEvent*,QPainter*);
    void buttonFixed();
    void destroyCard();
    void linkReset();
    virtual void changePaintMode(int mode,int information[3]);
    virtual void setResPara(int);
    virtual void dialogSet(bool canX[10]);
    virtual void setFrame();
    virtual void skillReset();
    virtual void changeSelfMode(int);
    virtual void skillCancel();
    virtual void magicSwordSet();
    void discard(int count);
    void append(int);
    int discardCount;
    int allCount;
    void missileAttack();
    virtual void priestAct();
    virtual void icePoetry();
signals:
    void isClicked(int x,int y);
    void resetSignal();
    void mouseClick(int x,int y);
    void skillSetSig();
    void sendMessageInSig(std::vector<int>);
    void sendMessageSelfSig(std::vector<int>);
    void sendMessageDisSig(std::vector<int>);
    void sendMessageMisSig(std::vector<int>);
    void sendMessageIceSig(std::vector<int>);
    void sendMessageOneSig(std::vector<int>);
    //void paintAnime(int info[15]);
public slots:
    void cardClicked(int x,int y);
    void send(int,int);
    //void paintSignal();
    void cardDis();
    void reset();
    virtual void dialogReset();
    virtual void skillset();
    virtual void selfReset();
    void discardPlus();
    void discardMinus();
    void sendMessageIn();
    void sendMessageDis();
    void sendMessageMis();
    void sendMessageIce();
    void sendMessageOne();
    void sendMessageCardAndSkill();
    virtual void sendMessageSelf();
};

#endif // CARDANDSKILL_H
