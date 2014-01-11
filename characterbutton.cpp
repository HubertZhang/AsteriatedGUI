//
//  characterbutton.cpp
//  AsteriatedGUI
//
//  Created by Hubert on 14-1-9.
//
//

#include "characterbutton.h"

CharacterButton::CharacterButton(int character, int place, QWidget* parent)
: PicButton(GEO_CHARACTER_X[place],GEO_CHARACTER_Y[place],GEO_CHARACTER_W,GEO_CHARACTER_H,true,parent)
{
    this->character = character;
    clickedLabel.setPixmap(QPixmap(QString(":/character/character%1.png").arg(QString::number(character))));
    notClickedLabel.setPixmap(QPixmap(QString(":/character/character%1.png").arg(QString::number(character))));
    frameLabel.setPixmap(QPixmap(QString(":/character/choosenFrame.png")));
}
CharacterButton::CharacterButton(int character, int xp, int yp, QWidget* parent)
: PicButton(xp,yp,GEO_CHARACTER_W,GEO_CHARACTER_H,true,parent)
{
    this->character = character;
    clickedLabel.setPixmap(QPixmap(QString(":/character/character%1.png").arg(QString::number(character))));
    notClickedLabel.setPixmap(QPixmap(QString(":/character/character%1.png").arg(QString::number(character))));
    frameLabel.setPixmap(QPixmap(QString(":/character/choosenFrame.png")));
}
int CharacterButton::getCharacter()
{
    return this->character;
}
