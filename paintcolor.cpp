#include "paintcolor.h"
#include <cstdlib>
PaintColor::PaintColor(int color[6],QWidget* parent) : QLabel(parent)
{
    this->setMinimumSize(GEO_SCREEN_W,GEO_SCREEN_H);
    if(color[5])
    {
        setPixmap(QPixmap(":/Frame/BlueFrame.png"));
    }
    else
    {
        setPixmap(QPixmap(":/Frame/RedFrame.png"));
    }
    for(int i = 0;i < 6;i++)
    {
        playerFrame[i].setParent(this);
        playerFrame[i].setGeometry(GEO_CHARACTER_X[i]-4, GEO_CHARACTER_Y[i]-4, GEO_CHARACTER_W+8, GEO_CHARACTER_H+8);
        if (color[i]==0) {
            playerFrame[i].setPixmap(QPixmap(":/character/redCharacterFrame.png"));
        }
        else playerFrame[i].setPixmap(QPixmap(":/character/blueCharacterFrame.png"));
    }
}

