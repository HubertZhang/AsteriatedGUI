#ifndef PAINTSTRUCT_H
#define PAINTSTRUCT_H
#include <QPixmap>
#include <QWidget>
#include <QLabel>
#include "cardList.h"
#include <QFont>
#include "characterbutton.h"
extern CardList cardlist;

class Character : QWidget
{
    Q_OBJECT
    QPixmap weakPic;
    QPixmap poisonPic;
    QPixmap sheildPic;
    QPixmap sealPic[6];
    
    QLabel statusBar[10];
    QLabel seal[6];
    QLabel gemLabel;
    QLabel crystalLabel;
    QLabel cureLabel;
    QLabel cardPic;
    QLabel numberPic[3];
//    QPixmap* isActivated;
//    QPixmap* choosenFrame;
public:
    CharacterButton* characterPic;
    bool canBeActivated;
    bool activated;
    bool blueExist;
    bool yellowExist;
    int color;//red for 0 and blue for 1;
    int characterNum;
    int cardNum;
    int cardLimit;
    int energeLimit;
    int cure;
    int cureLimit;
    int gem;
    int crystal;
    int status[10];
    int statusNum;
    int blue;
    int yellow;
public:
    int getCure(){return cure;}
    //TODO: change these to private
    Character(int characterNum,int place,int color,QWidget* parent);
protected:
    void paintEvent(QPaintEvent*);
//    int xp;
//    int yp;
//    int width;
//    int height;
//    int offsetX;
//    int offsetY;

};

class PaintStruct : public QWidget
{    
    Q_OBJECT
private:
//    
//    //QPixmap* arrow[4];
//    QPixmap* soulY;
//    //QPixmap* soulB;
//    //QPixmap* cardFrame;
//    //QPixmap* gem;
//    //QPixmap* crystal;
//    QLabel grail;
//
//    QPixmap* seal[6];
public:
    //CardAndSkill* cardAndSkill;
    Character* gameCharacter[6];
    int yourSite;
    int arrowNum;
    int paintArrow;
//    int arrowX[6];
//    int arrowY[6];
    int grailRed;
    int grailBlue;
    int gemRed;
    int gemBlue;
    int crystalRed;
    int crystalBlue;
    int moraleRed;
    int moraleBlue;
    QLabel redGrailPic[5];
    QLabel blueGrailPic[5];
    QLabel redStonePic[5];
    QLabel blueStonePic[5];
    
    QLabel redMoralePic;
    QLabel blueMoralePic;
    QPixmap crystalPic;
    QPixmap gemPic;
    int SoulYX[6];
    int SoulYY[6];
    int SoulBX[6];
    int SoulBY[6];
protected:
    void paintEvent(QPaintEvent* event);
public:
    explicit PaintStruct(int information[15],int yourX, QWidget* parent);
};

bool getBlue(int characterNum);
bool getYellow(int characterNum);
int getCrystal(int characterNum);
int getCureLimit(int chracterNum);
int getEnergyLimit(int characterNum);
bool ifActivated(int characterNum);
#endif // PAINTSTRUCT_H
