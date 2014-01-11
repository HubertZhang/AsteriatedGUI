#ifndef CARDANDSKILL_H
#define CARDANDSKILL_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QButtonGroup>
#include <vector>
#include "cardbutton.h"
#include "paintstruct.h"
#include "cardList.h"
#include "card.h"
#include "framelabel.h"
using std::vector;
//extern class PaintStruct;
class CardAndSkill : public QWidget
{
    Q_OBJECT
public:
    PaintStruct* paintStruct;
    QWidget* windowX;
    CardList* cardList;
    FrameLabel* frameLabel;
    int paintMode;
    bool frame;
    bool cancelClick;
//    QButtonGroup cardGroup;
//    vector<CardButton*> cardButton;
//    QButtonGroup characterGroup;
    CardButton* cardButton[15];
    PicButton* ensure;
    PicButton* cancel;
    int card[15];
    int cardNum;
    int informationKind;
    explicit CardAndSkill(PaintStruct* paintStruct,QWidget *parent);
    //virtual void paint(QPaintEvent*,QPainter*);
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
    void putCharacter(std::vector<int> &);
    void putCard(std::vector<int> &);
    void putCharacterCount(std::vector<int> &);
    void putCardCount(std::vector<int> &);
    void discard(int count);
    void append(int);
    int discardCount;
    int allCount;
    void missileAttack();
    virtual void priestAct();
    virtual void icePoetry();
    virtual void arbitrationEnd();
    virtual void lastAttackSet(int);
    virtual void YuukaOne();
    virtual void YuukaTwo();
    virtual void damageSet(int);
    virtual bool redWhiteLink();
    virtual void lifeLinkOver();
    virtual void clickRedWhiteSet();
    virtual void butterflyTokenAdd(int tokenX[]);
signals:
    //void isClicked(int x,int y);
    void resetSignal();
    //void mouseClick(int x,int y);
    void skillSetSig();
    void sendMessageInSig(std::vector<int>);
    void sendMessageSelfSig(std::vector<int>);
    void sendMessageDisSig(std::vector<int>);
    void sendMessageMisSig(std::vector<int>);
    void sendMessageIceSig(std::vector<int>);
    void sendMessageOneSig(std::vector<int>);
    //void paintAnime(int info[15]);
public slots:
    //void cardClicked(int x,int y);
    //void send(int,int);
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
    void clickRivalSet();
    void clickAllSet();
    void singleToEnsure();
    void cardSingleSet(int);
    void cardSingle();
    void allReset();
    void cardResetOne();
    void cardSetOne();
    void clickFriendSet();
    void characterDisconnect();
};

#endif // CARDANDSKILL_H
