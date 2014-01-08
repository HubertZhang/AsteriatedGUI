#include "picbutton.h"
#include <cstdlib>
#include <QString>
#include <iostream>
PicButton::PicButton(int buttonKind,int paraX,int paraY,int paraW,int paraH,bool canBe,QWidget* parent) : QPushButton(parent)
{
    setCheckable(true);
    setChecked(false);
    setEnabled(canBe);
    setGeometry(paraX, paraY, paraW, paraW);
    clickedLabel.setParent(this);
    notClickedLabel.setParent(this);
    frameLabel.setParent(this);
    clickedLabel.setGeometry(paraX, paraY, paraW, paraW);
    notClickedLabel.setGeometry(paraX, paraY, paraW, paraW);
    frameLabel.setGeometry(paraX, paraY, paraW, paraW);
    this->setStyleSheet("border:none;");
    
    QString s;
    kind = buttonKind;
    s.sprintf(":/button/buttonNotClicked%d.png",buttonKind);
    notClickedMap = new QPixmap();
    notClickedMap->load(s);
    clickedMap = new QPixmap();
    if(buttonKind < 25)
    {
        s.sprintf(":/character/character%d.png",buttonKind);
        //system("pause");
        clickedMap->load(s);
        notClickedMap->load(s);
    }
    else
    {
        s.sprintf(":/button/buttonClicked%d.png",buttonKind);
        clickedMap->load(s);
    }
    
    switch(paraW)
    {
        case 100:
        {
            s.sprintf(":/character/buttonFrame100.png");
            break;
        }
        case 50:
        {
            if(paraH == 42)
            {
                s.sprintf(":/character/buttonFrame50.png");
                break;
            }
            else
            {
                s.sprintf(":/character/cureFrame.png");
            }
        }
        case 48:
        {
            s.sprintf(":/character/cardFrameX.png");
        }
        default:
        {
            s.sprintf(":/character/choosenFrame.png");
        }
    }
    frame = new QPixmap();
    frame->load(s);
    clickedLabel.setPixmap(*clickedMap);
    notClickedLabel.setPixmap(*notClickedMap);
    frameLabel.setPixmap(*frame);
    connect(this, SIGNAL(clicked()), this, SLOT(isThisClicked()));
}//buttonKind from 1 to 31:For characterPic;
void PicButton::isThisClicked()
{
    if(isChecked())
    {
        frameLabel.setVisible(true);
        notClickedLabel.setVisible(false);
        frameLabel.setVisible(true);
        emit beChecked();
    }
    else
    {
        clickedLabel.setVisible(false);
        notClickedLabel.setVisible(true);
        frameLabel.setVisible(false);
        emit unChecked();
    }
}

//void PicButton::cancelX()
//{
//    //setChecked(false);
//}
//void PicButton::recover()
//{
//    //setChecked(true);
//}
void PicButton::setState(bool state)
{
    setEnabled(state);
}
void PicButton::disable()
{
    setEnabled(false);
    //setCheckable(false);
    //setChecked(false);
    //isClicked  = false;
}
void PicButton::enable()
{
    setEnabled(true);
    //setCheckable(true);
}
