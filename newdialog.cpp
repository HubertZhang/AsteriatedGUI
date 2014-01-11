#include "newdialog.h"
#include <QString>
NewDialog::NewDialog(QWidget *parent) :
    QLabel(parent)
{
    label = new QLabel(parent);
    setGeometry(328,247,520,280);
    setPixmap(QPixmap(":/character/chooseCharacterFrame"));
    label->move(25,20);
    skillCount = 0;

    font = new QFont();
    font->setPointSize(30);
    font->setBold(true);
    palette = new QPalette();
    palette->setColor(QPalette::WindowText,Qt::yellow);
    label->setPalette(*palette);
    label->setFont(*font);
    label->setText(QString::fromUtf8("请选择响应"));
}
void NewDialog::init(int chara)
{
    switch(chara)
    {
        case 1:
        {
            skillCount = 4;
            skillGroup[0] = new PicButton(54, 25,232,100,42,false,this);
            skillGroup[1] = new PicButton(55, 150,232,100,42,false,this);
            skillGroup[2] = new PicButton(56, 275,232,100,42,false,this);
            skillGroup[3] = new PicButton(57, 400,232,100,42,false,this);
            break;
        }
        case 2:
        {
            skillCount = 3;
            skillGroup[0] = new PicButton(58, 25,232,100,42,false,this);
            skillGroup[1] = new PicButton(59, 150,232,100,42,false,this);
            skillGroup[2] = new PicButton(60, 275,232,100,42,false,this);
            break;
        }
        case 3:
        {
            skillCount = 2;
            skillGroup[0] = new PicButton(61, 25,232,100,42,false,this);
            skillGroup[1] = new PicButton(63, 150,232,100,42,false,this);
            break;
        }
        case 4:
        {
            skillCount = 1;
            skillGroup[0] = new PicButton(65, 25,232,100,42,false,this);
            break;
        }
        case 5:
        {
            skillCount = 1;
            skillGroup[0] = new PicButton(69, 25,232,100,42,false,this);
            break;
        }
        case 7:
        {
            skillCount = 2;
            skillGroup[0] = new PicButton(78, 25,232,100,42,false,this);
            skillGroup[1] = new PicButton(79, 150,232,100,42,false,this);
            break;
        }
        case 8:
        {
            skillCount = 1;
            skillGroup[0] = new PicButton(81, 25,232,100,42,false,this);
            break;
        }
        case 9:
        {
            skillCount = 2;
            skillGroup[0] = new PicButton(83, 25,232,100,42,false,this);
            skillGroup[1] = new PicButton(86, 150,232,100,42,false,this);
            break;
        }
        case 10:
        {
            skillCount = 2;
            skillGroup[0] = new PicButton(89, 25,232,100,42,false,this);
            skillGroup[1] = new PicButton(90, 150,232,100,42,false,this);
            break;
        }
        case 13:
        {
            skillCount = 1;
            skillGroup[0] = new PicButton(101, 25,232,100,42,false,this);
            break;
        }
        case 15:
        {
            skillCount = 1;
            skillGroup[0] = new PicButton(107, 25,232,100,42,false,this);
            break;
        }
        case 16:
        {
            skillCount = 1;
            skillGroup[0] = new PicButton(118, 25,232,100,42,false,this);
            break;
        }
        case 17:
        {
            skillCount = 1;
            skillGroup[0] = new PicButton(119, 25,232,100,42,false,this);
            break;
        }
        case 18:
        {
            skillCount = 3;
            skillGroup[0] = new PicButton(124, 25,232,100,42,false,this);
            skillGroup[1] = new PicButton(125, 150,232,100,42,false,this);
            skillGroup[2] = new PicButton(126, 275,232,100,42,false,this);
            break;
        }
        case 19:
        {
            skillCount = 5;
            skillGroup[0] = new PicButton(128, 25,232 - 50,100,42,false,this);
            skillGroup[1] = new PicButton(129, 25,232,100,42,false,this);
            skillGroup[2] = new PicButton(130, 150,232,100,42,false,this);
            skillGroup[3] = new PicButton(131, 275,232,100,42,false,this);
            skillGroup[4] = new PicButton(132, 400,232,100,42,false,this);
            break;
        }
        case 20:
        {
            skillCount = 3;
            skillGroup[0] = new PicButton(133, 25,232,100,42,false,this);
            skillGroup[1] = new PicButton(134, 150,232,100,42,false,this);
            skillGroup[2] = new PicButton(136, 275,232,100,42,false,this);
            break;
        }
        case 21:
        {
            skillCount = 4;
            skillGroup[0] = new PicButton(138, 25,232,100,42,false,this);
            skillGroup[1] = new PicButton(139, 150,232,100,42,false,this);
            skillGroup[2] = new PicButton(141, 275,232,100,42,false,this);
            skillGroup[3] = new PicButton(142, 400,232,100,42,false,this);
            break;
        }
        case 22:
        {
            skillCount = 3;
            skillGroup[0] = new PicButton(144, 25,232,100,42,false,this);
            skillGroup[1] = new PicButton(145, 150,232,100,42,false,this);
            skillGroup[2] = new PicButton(149, 275,232,100,42,false,this);
            break;
        }
        case 24:
        {
            skillCount = 4;
            skillGroup[0] = new PicButton(158, 25,232,100,42,false,this);
            skillGroup[1] = new PicButton(159, 150,232,100,42,false,this);
            skillGroup[2] = new PicButton(160, 275,232,100,42,false,this);
            skillGroup[3] = new PicButton(161, 400,232,100,42,false,this);
            break;
        }
        case 101:
        {
            skillCount = 10;
            for(int i = 0;i < 3;i++)
            {
                skillGroup[i] = new PicButton(200 + i, 25 + 125 * i,232 - 150,100,42,false,this);
            }
            for(int i = 3;i < 7;i++)
            {
                skillGroup[i] = new PicButton(200 + i, 25 + 125 * (i - 3),232 - 90,100,42,false,this);
            }
            for(int i = 7;i < 10;i++)
            {
                skillGroup[i] = new PicButton(200 + i, 25 + 125 * (i - 7),232 - 30,100,42,false,this);
            }
            break;
        }
    }
}
void NewDialog::set(bool canX[])
{
    for(int i = 0;i < skillCount;i++)
    {
        if(canX[i])
        {
            skillGroup[i]->setEnabled(true);
        }
    }
}
