#ifndef PAINTSTRUCT_H
#define PAINTSTRUCT_H
#include <QPixmap>
#include <QWidget>
#include <QLabel>
#include "cardList.h"
#include <QFont>
#include "picbutton.h"
struct character
{
    PicButton* characterPic;
    QPixmap* isActivated;
    QPixmap* choosenFrame;
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
    int xp;
    int yp;
    int width;
    int height;
    int offsetX;
    int offsetY;
    int blue;
    int yellow;
};

class PaintStruct : public QWidget
{    
    Q_OBJECT
private:
    QPixmap* redNum[17];
    QPixmap* blueNum[17];
    QPixmap* arrow[4];
    QPixmap* attribute[6];
    QPixmap* soulY;
    QPixmap* soulB;
    QPixmap* cardFrame;
    QPixmap* gem;
    QPixmap* crystal;
    QPixmap* grail;
    QPixmap* weakPic;
    QPixmap* poisonPic;
    QPixmap* sheildPic;
    QPixmap* number[17];
    QPixmap* slash;
    QFont* font;
    CardList* cardList;
public:
    character* gameCharacter[6];
    int arrowNum;
    int paintArrow;
    int arrowX[6];
    int arrowY[6];
    int grailRed;
    int grailBlue;
    int gemRed;
    int gemBlue;
    int crystalRed;
    int crystalBlue;
    int moraleRed;
    int moraleBlue;
    int SoulYX[6];
    int SoulYY[6];
    int SoulBX[6];
    int SoulBY[6];
    bool getBlue(int characterNum);
    bool getYellow(int characterNum);
    int getCrystal(int characterNum);
    int getCureLimit(int chracterNum);
    int getEnergyLimit(int characterNum);
    bool ifActivated(int characterNum);
    void paint(QPaintEvent*,QPainter*);
    explicit PaintStruct(int information[15],QWidget* parent);
};

#endif // PAINTSTRUCT_H
