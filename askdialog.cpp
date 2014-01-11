#include "askdialog.h"
//#include "window.h"
//#include <cstdlib>
//#include <iostream>
#include <QDebug>
using namespace std;
AskDialog::AskDialog(PaintStruct* paintStruct,QWidget* parent) : QLabel(parent)
{
    setGeometry(GEO_DIALOG_X, GEO_DIALOG_Y, GEO_DIALOG_W, GEO_DIALOG_H);
    setPixmap(QPixmap(":/character/chooseCharacterFrame.png"));
    this->paintStruct = paintStruct;
    font.setPointSize(30);
    font.setBold(true);
    palette.setColor(QPalette::WindowText,Qt::yellow);
    ensure = new PicButton(32,GEO_DIALOG_ENSURE_X, GEO_DIALOG_ENSURE_Y, GEO_DIALOG_ENSURE_W, GEO_DIALOG_ENSURE_H, false , this);
    ensure->setEnabled(false);
    cancel = new PicButton(33,GEO_DIALOG_CANCEL_X, GEO_DIALOG_CANCEL_Y, GEO_DIALOG_CANCEL_W, GEO_DIALOG_CANCEL_H, false,this);
    operate.addButton(ensure);
    operate.addButton(cancel);
    show();
    connect(ensure, SIGNAL(clicked()), this, SLOT(ensureClicked()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(cancelClicked()));
}
void AskDialog::ensureClicked(){return;};
void AskDialog::cancelClicked(){return;};
WeakDialog::WeakDialog(PaintStruct* paintStruct,QWidget* parent) : AskDialog(paintStruct,parent)
{
    text.setParent(this);
    text.setText(QString::fromUtf8("询问虚弱: 确定跳过回合,\n取消接三张牌."));
    text.setFont(font);
    text.setPalette(palette);
    text.move(25,20);
    text.show();
}
void WeakDialog::ensureClicked()
{
    std::vector<int> tempMes;
    tempMes.push_back(1);
    emit sendMessageWeakSig(tempMes);
    this->deleteLater();
}
void WeakDialog::cancelClicked()
{
    std::vector<int> tempMes;
    tempMes.push_back(0);
    emit sendMessageWeakSig(tempMes);
    this->deleteLater();
}
CureDialog::CureDialog(int damage,PaintStruct* paintStruct,QWidget* parent) : AskDialog(paintStruct,parent)
{
    PicButton* cureButton[5];
    int cureNum = paintStruct->gameCharacter[5]->getCure();
    cure.setExclusive(true);
    for (int i = 0;i<5; i++) {
        cureButton[i] = new PicButton(99 + 70 * i,(407-247),50,50,true,this);
        cureButton[i]->setNumber(i+1);
        if (i>=cureNum||i>damage) {
            cureButton[i]->setDisabled(true);
        }
        cure.addButton(cureButton[i],i);
    }
}
void CureDialog::ensureClicked()
{
    std::vector<int> tempMes;
    if (cure.checkedId()==-1) {
        tempMes.push_back(0);
        emit sendMessageCureSig(tempMes);
    }
    else
    {
        tempMes.push_back(cure.checkedId()+1);
        emit sendMessageCureSig(tempMes);
    }
    this->deleteLater();
}

void CureDialog::cancelClicked(){
    std::vector<int> tempMes;
    tempMes.push_back(0);
    emit sendMessageCureSig(tempMes);
    this->deleteLater();
}
NumberDialog::NumberDialog(PaintStruct* paintStruct,QWidget* parent) : AskDialog(paintStruct,parent)
{
    for (int i = 0;i<5; i++) {
        number[i] = new PicButton(99 + 70 * i,(407-247),50,50,true,this);
        number[i]->setNumber(i+1);
    }
}
void NumberDialog::ensureClicked()
{
    std::vector<int> tempMes;
//    if (cure.checkedId()==-1) {
//        tempMes.push_back(0);
//        emit sendMessageCureSig(tempMes);
//    }
//    else
//    {
//        tempMes.push_back(cure.checkedId()+1);
//        emit sendMessageCureSig(tempMes);
//    }
    this->deleteLater();
}

void NumberDialog::cancelClicked(){
    std::vector<int> tempMes;
//    tempMes.push_back(0);
//    emit sendMessageCureSig(tempMes);
    this->deleteLater();
}
ActiveDialog::ActiveDialog(PaintStruct* paintStruct,QWidget* parent) : AskDialog(paintStruct,parent)
{
    int offsetX = 0;
    int offsetY = 12 + 42;
    ensure->setEnabled(false);
    cancel->setEnabled(true);
    choice.setExclusive(true);
    PicButton* choiceButton[4];
    //Active
    int characterNum = paintStruct->gameCharacter[5]->characterNum;
    int skill1,skill2;
    bool activateAllow=false;
    PicButton* activateButton[2];
    active.setExclusive(true);
    getActivatedSkill(characterNum,skill1,skill2);
    if (skill1) {
        activateButton[0] = new PicButton(109,9,100,42,true,this);
        if (!canActivate(characterNum,1)) {
            activateButton[0]->setEnabled(false);
        }
        else activateAllow = true;
        active.addButton(activateButton[0],0);
    }
    if (skill2) {
        activateButton[1] = new PicButton(209,9,100,42,true,this);
        if (!canActivate(characterNum,2)) {
            activateButton[1]->setEnabled(false);
        }
        active.addButton(activateButton[1],1);
    }
    choiceButton[0] = new PicButton(34,9+offsetX,9,100,42,true,this);
    choiceButton[0]->setEnabled(activateAllow);
    choice.addButton(choiceButton[0],0);
    //Refine
    PicButton* refineButton[5];
    bool refineAllow = false;
    int color = paintStruct->gameCharacter[5]->color;
    int teamStone,teamGem,teamCrystal;
    int playerGem = paintStruct->gameCharacter[5]->gem;
    int playerCrystal = paintStruct->gameCharacter[5]->crystal;
    int energyLimit= paintStruct->gameCharacter[5]->energeLimit;
    if(color)
    {
        teamCrystal =paintStruct->crystalBlue;
        teamGem =paintStruct->gemBlue;
        teamStone = teamGem+teamCrystal;
    }
    else
    {
        teamCrystal =paintStruct->crystalRed;
        teamGem =paintStruct->gemRed;
        teamStone = teamGem+teamCrystal;
    }

    if(teamStone && (playerCrystal+playerGem<energyLimit))
    {
        refineAllow = true;
    }
    
    for (int i = 0; i<5; i++) {
        refineButton[i] = new PicButton(109+100*i+offsetX,9+offsetY,100,42,true,this);
        refineButton[i]->setRefine(i);
        refineButton[i]->setEnabled(refineAllow);
        refine.addButton(refineButton[i],i);
    }
    if (refineAllow) {
        if (teamGem<1)
        {
            refineButton[2]->setEnabled(false);
            refineButton[4]->setEnabled(false);
            refineButton[5]->setEnabled(false);
        }
        if (teamCrystal<1) {
            refineButton[1]->setEnabled(false);
            refineButton[3]->setEnabled(false);
            refineButton[4]->setEnabled(false);
        }
    }
    if (characterNum == 12)
    {
        for (int i = 0; i<6; i++) {
            players.addButton(paintStruct->gameCharacter[i]->characterPic);
        }
    }
    choiceButton[1] = new PicButton(35,9+offsetX,9+offsetY,100,42,refineAllow,this);
    choice.addButton(choiceButton[1],1);
    //buy
    PicButton* buyButton[3];
    bool buyAllow = false;
    if(paintStruct->gameCharacter[5]->cardLimit - paintStruct->gameCharacter[5]->cardNum > 2)
    {
        buyAllow = true;
    }

    for(int i = 0;i < 3;i++)
    {
        buyButton[i] = new PicButton(109+100 * i,9+offsetY * 2,100,42,true,this);
        buy.addButton(buyButton[i],i);
    }
    buyButton[0]->setByNumber(43);
    buyButton[1]->setByNumber(44);
    if (characterNum==12) {
        buyButton[2]->setByNumber(46);
    }
    else buyButton[2]->setByNumber(41);

    if(teamStone == 5)
    {
        for (int i = 0; i<3; i++) {
            buyButton[i]->setEnabled(false);
        }
    }
    else if(teamStone == 4)
    {
        buyButton[2]->setEnabled(false);
        if(characterNum == 12)
        {
            buyButton[1]->setEnabled(false);
        }
    }
    choiceButton[2] = new PicButton(36,9 + offsetX,9+ offsetY * 2,100,42,buyAllow,this);
    choice.addButton(choiceButton[2],2);
    //Compose
    PicButton* composeButton[4];
    bool composeAllow = false;
    if (teamStone>3&&buyAllow) {
        composeAllow = true;
    }
    for(int i = 0;i < 4;i++)
    {
        composeButton[i] = new PicButton(44+i,109+100*i,9+offsetY*3,100,42,true,this);
        composeButton[i]->setEnabled(false);
        compose.addButton(composeButton[i],i);
        if (teamGem>=i) {
            composeButton[i]->setEnabled(true);
        }
    }
    choiceButton[3] = new PicButton(37,9 + offsetX, 9+offsetY * 3,100,42,composeAllow,this);
    choice.addButton(choiceButton[3],3);
    connect(&choice, SIGNAL(buttonClicked(int)), ensure, SLOT(enable()));
}

void ActiveDialog::ensureClicked()
{
    qDebug() << choice.checkedId();
    vector<int> tempMes;
    switch (choice.checkedId()) {
        case 0:
            if (active.checkedId()!=-1)
            {
                tempMes.push_back(1);
                tempMes.push_back(active.checkedId());
                emit sendMessageSpeSig(tempMes);
                emit activateSig((active.checkedId()==0), (active.checkedId()==1));
                this->deleteLater();
            }
            break;
        case 1:
            if (refine.checkedId()!=-1) {
                tempMes.push_back(2);
                int type = refine.checkedId();
                switch (type) {
                    case 0:
                        tempMes.push_back(1);
                        tempMes.push_back(0);
                        break;
                    case 1:
                        tempMes.push_back(0);
                        tempMes.push_back(1);
                        break;
                    case 2:
                        tempMes.push_back(2);
                        tempMes.push_back(0);
                        break;
                    case 3:
                        tempMes.push_back(1);
                        tempMes.push_back(1);
                        break;
                    case 4:
                        tempMes.push_back(0);
                        tempMes.push_back(2);
                        break;
                    default:
                        break;
                }
                if(paintStruct->gameCharacter[5]->characterNum == 12)
                {
                    if (players.checkedId()!=-1) {
                        int site = (-players.checkedId() + paintStruct->yourSite + 5) % 6;
                        tempMes.push_back(site);
                        //TODO: check this!
                        for (int i = 0; i<6; i++) {
                            players.button(i)->setChecked(false);
                            players.removeButton(players.button(i));
                        }
                        players.deleteLater();
                    }
                }
                emit sendMessageSpeSig(tempMes);
                this->deleteLater();
            }
            break;
        case 2:
            if (buy.checkedId()!=-1) {
                tempMes.push_back(3);
                switch (buy.checkedId()) {
                    case 0:
                        tempMes.push_back(1);
                        tempMes.push_back(0);
                        break;
                    case 1:
                        tempMes.push_back(0);
                        tempMes.push_back(1);
                        break;
                    case 2:
                        if (paintStruct->gameCharacter[5]->characterNum == 12)
                        {
                            tempMes.push_back(0);
                            tempMes.push_back(2);
                            break;
                        }
                        tempMes.push_back(1);
                        tempMes.push_back(1);
                        break;
                    default:
                        break;
                }
                emit sendMessageSpeSig(tempMes);
                this->deleteLater();
            }
            break;
        case 3:
            if (compose.checkedId()!=-1) {
                
                tempMes.push_back(4);
                tempMes.push_back(3-compose.checkedId());
                tempMes.push_back(compose.checkedId());
                
                emit sendMessageSpeSig(tempMes);
                this->deleteLater();
            }
            break;
        default:
            break;
    }
    return;
}
void ActiveDialog::cancelClicked()
{
    std::vector<int> tempMes;
    tempMes.push_back(0);
    emit sendMessageSpeSig(tempMes);
    this->deleteLater();
    return;
}

int ActiveDialog::getActivatedNum(int characterNum)
{
    switch(characterNum)
    {
        case 5:
        case 6:
        case 9:
        case 15:
        case 16:
        {
            return 1;
            break;
        }
        case 14:
        case 20:
        case 22:
        case 23:
        {
            return 2;
            break;
        }
        default:
        {
            return 0;
            break;
        }
    }
}

void ActiveDialog::getActivatedSkill(int characterNum,int& skill1, int& skill2)
{
    skill1 = 0;
    skill2 = 0;
    switch(characterNum)
    {
        case 5:
        {
            skill1 = 70;
            break;
        }
        case 6:
        {
            skill1 = 73;
            break;
        }
        case 9:
        {
            skill1 = 84;
            break;
        }
        case 14:
        {
            skill1 = 102;
            skill2 = 104;
            break;
        }
        case 15:
        {
            skill1 = 110;
            break;
        }
        case 16:
        {
            skill1 = 117;
            break;
        }
        case 20:
        {
            skill1 = 135;
            skill2 = 137;
            break;
        }
        case 22:
        {
            skill1 = 149;
            skill2 = 150;
            break;
        }
        case 23:
        {
            skill1 = 152;
            skill2 = 153;
            break;
        }
        default:
        {
            break;
        }
    }
}

bool ActiveDialog::canActivate(int characterNum, int skill)
{
    int skillNum = characterNum * 10 + skill;
    Character* player = paintStruct->gameCharacter[5];
    switch(skillNum)
    {
        case 51:
        {
            if(player->gem != 0)
            {
                return true;
            }
            else
            {
                return false;
            }
            break;
        }
        case 61:
        {
            if(player->gem != 0 && !player->activated)
            {
                return true;
            }
            else
            {
                return false;
            }
            break;
        }
        case 91:
        {
            return true;
            break;
        }
        case 151:
        {
            if((player->crystal != 0 || player->gem != 0) && player->cure != 0)
            {
                return true;
            }
            else
            {
                return false;
            }
            break;
        }
        case 161:
        {
            if(player->gem != 0 && !player->activated)
            {
                return true;
            }
            else
            {
                return false;
            }
            break;
        }
        case 141:
        {
            if(player->activated)
            {
                return true;
            }
            else
            {
                return false;
            }
            break;
        }
        case 142:
        {
            if(player->gem != 0 && !player->activated)
            {
                return true;
            }
            else
            {
                return false;
            }
            break;
        }
        case 201:
        {
            if(player->yellow > 2)
            {
                return true;
            }
            else
            {
                return false;
            }
            break;
        }
        case 202:
        {
            if(player->gem != 0 || player->crystal != 0)
            {
                return true;
            }
            else
            {
                return false;
            }
            break;
        }
        case 221:
        {
            if(player->yellow > 0 && player->blue > 0 && !player->activated)
            {
                return true;
            }
            else
            {
                return false;
            }
            break;
        }
        case 222:
        {
            if(player->gem != 0)
            {
                return true;
            }
            else
            {
                return false;
            }
            break;
        }
        case 231:
        case 232:
        {
            return true;//paintStruct->cardAndSkill->redWhiteLink();
            break;
        }
        default:
        {
            return true;
            break;
        }
    }
}

SpecialDialog::SpecialDialog(PaintStruct* paintStruct,QWidget* parent) : AskDialog(paintStruct,parent)
{
    labelOne = new QLabel(this);
    labelTwo = new QLabel(this);
    labelOne->setFont(font);
    labelTwo->setFont(font);
    labelOne->setPalette(palette);
    labelTwo->setPalette(palette);
    labelOne->move(25, 20);
    labelTwo->move(25, 60);
}

void SpecialDialog::ensureClicked()
{
    
}
void SpecialDialog::cancelClicked()
{
    
}
int wast()
{
//AskDialog::AskDialog(int information[3],PaintStruct* paintStruct,bool redWhiteLink,QWidget *parent) : QLabel(parent)
//{
//    redWhite = redWhiteLink;
//    informationKind = 0;
//    storeData = paintStruct;
//    //storeWindow = parent;
//    setPixmap(QPixmap(":/character/chooseCharacterFrame.png"));
//    setGeometry(328,247, 520, 280);
//    ensure = new PicButton((595-328),(479-247),100,42,false,this);
//    cancel = new PicButton( 715-328 , 479-247,100,42,false,this);
//    connect(ensure,SIGNAL(clicked()),this,SLOT(sendMessageAskDialog()));
//    connect(cancel,SIGNAL(clicked()),this,SLOT(sendMessageAskDialog()));
//
//    labelOne = new QLabel(this);
//    labelTwo = new QLabel(this);
//    for(int i = 0;i < 3;i ++)
//    {
//        kind[i] = information[i];
//    }
//    font = new QFont();
//    font->setPointSize(30);
//    font->setBold(true);
//    palette = new QPalette();
//    palette->setColor(QPalette::WindowText,Qt::yellow);
////    if(kind[0] == 0)
////    {
////        //ensure->setCheckable(true);
////        labelOne->setText(QString::fromUtf8("询问虚弱: 确定跳过回合,"));
////        labelOne->setFont(*font);
////        labelOne->setPalette(*palette);
////        labelOne->move(328 + 25,247 + 20);
////        labelOne->show();
////        labelTwo->setText(QString::fromUtf8("取消接三张牌."));
////        labelTwo->setFont(*font);
////        labelTwo->setPalette(*palette);
////        labelTwo->move(328 + 25,247 + 60);
////        labelTwo->show();
////        //delete s;
////    }
//    if(kind[0] == 1)
//    {
//        ensure->setCheckable(false);
//        int offsetX = 0;
//        int offsetY = 12 + 42;
//        actNum = getActivatedNum(storeData->gameCharacter[5]->characterNum);
//        bool activateTwo[2];
//        activeInit(storeData->gameCharacter[5]->characterNum);
//        //system("pause");
//        for(int i = 0;i < 2;i++)
//        {
//            activateTwo[i] = false;
//        }
//        bool activateAllow = false;
//        if(actNum == 1)
//        {
//            activateTwo[0] = canActivate(1);
//            activateAllow = canActivate(1);
//            //system("pause");
//            activateGroup[0]->canBeClicked = activateTwo[0];
//        }
//        //system("pause");
//        if(actNum == 2)
//        {
//            activateTwo[0] = canActivate(1);
//            activateTwo[1] = canActivate(2);
//            activateAllow = activateTwo[0] || activateTwo[1];
//            activateGroup[0]->canBeClicked = activateTwo[0];
//            activateGroup[1]->canBeClicked = activateTwo[1];
//        }
//        //system("pause");
//        attributeGroup[0] = new PicButton(34,9 + 328 + offsetX,257,100,42,activateAllow);
////        bool refineAllow = false;
////        int color = storeData->gameCharacter[5]->color;
////        int stone = 0;
////        if(color)
////        {
////            stone = storeData->crystalBlue + storeData->gemBlue;
////        }
////        else
////        {
////            stone = storeData->crystalRed + storeData->gemRed;
////        }
////        if(stone && (storeData->gameCharacter[5]->gem + storeData->gameCharacter[5]->crystal != storeData->gameCharacter[5]->energeLimit))
////        {
////            refineAllow = true;
////        }
////        attributeGroup[1] = new PicButton(35,9 + 328 + offsetX,257 + offsetY,100,42,refineAllow);
////        int crystalExist = 0;
////        int gemExist = 0;
////        if(color)
////        {
////            crystalExist = storeData->crystalBlue;
////            gemExist = storeData->gemBlue;
////        }
////        else
////        {
////            crystalExist = storeData->crystalRed;
////            gemExist = storeData->gemRed;
////        }
////        bool refine[5];
////        for(int i = 0;i < 5;i++)
////        {
////            refine[i] = false;
////        }
////        if(!crystalExist && !gemExist)
////        {
////        }
////        if(!crystalExist && gemExist == 1)
////        {
////            refine[0] = true;
////        }
////        if(!gemExist && crystalExist == 1)
////        {
////            refine[1] = true;
////        }
////        if(!crystalExist && gemExist > 1)
////        {
////            refine[0] = true;
////            refine[2] = true;
////        }
////        if(!gemExist && crystalExist > 1)
////        {
////            refine[1] = true;
////            refine[4] = true;
////        }
////        if(gemExist == 1 && crystalExist == 1)
////        {
////            refine[0] = true;
////            refine[1] = true;
////            refine[3] = true;
////        }
////        if(gemExist > 1 && crystalExist == 1)
////        {
////            refine[0] = true;
////            refine[1] = true;
////            refine[2] = true;
////            refine[3] = true;
////        }
////        if(gemExist == 1 && crystalExist > 1)
////        {
////            refine[0] = true;
////            refine[1] = true;
////            refine[3] = true;
////            refine[4] = true;
////        }
////        if(gemExist > 1 && crystalExist > 1)
////        {
////            for(int i = 0;i < 5;i++)
////            {
////                refine[i] = true;
////            }
////        }
////        stone = storeData->gameCharacter[5]->crystal + storeData->gameCharacter[5]->gem;
////        if(storeData->gameCharacter[5]->energeLimit == stone)
////        {
////            for(int i = 0;i < 5;i++)
////            {
////                refine[i] = false;
////            }
////        }
////        if(storeData->gameCharacter[5]->energeLimit == stone + 1)
////        {
////            for(int i = 2;i < 5;i++)
////            {
////                refine[i] = false;
////            }
////        }
////        if(!refineAllow)
////        {
////            for(int i = 0;i < 5;i++)
////            {
////                refine[i] = false;
////            }
////        }
////        refineGroup[0] = new PicButton(38,9 + 328 + 100 + offsetX * 2,257 + offsetY,50,42,refine[0]);
////        refineGroup[1] = new PicButton(39,9 + 328 + 100 + 50 + offsetX * 3,257 + offsetY,50,42,refine[1]);
////        refineGroup[2] = new PicButton(40,9 + 328 + 100 + 50 * 2 + offsetX * 4,257 + offsetY,100,42,refine[2]);
////        refineGroup[3] = new PicButton(41,9 + 328 + 100 * 2 + 50 * 2 + offsetX * 5,257 + offsetY,100,42,refine[3]);
////        refineGroup[4] = new PicButton(42,9 + 328 + 100 * 3 + 50 * 2 + offsetX * 6,257 + offsetY,100,42,refine[4]);
////        bool buyAllow = false;
////        if(storeData->gameCharacter[5]->cardLimit - storeData->gameCharacter[5]->cardNum > 2)
////        {
////            buyAllow = true;
////        }
////        bool buy[4];
////        for(int i = 0;i < 4;i++)
////        {
////            buy[i] = false;
////        }
////        if(color)
////        {
////            stone = storeData->gemBlue + storeData->crystalBlue;
////        }
////        else
////        {
////            stone = storeData->gemRed + storeData->crystalRed;
////        }
////        attributeGroup[2] = new PicButton(36,9 + 328 + offsetX,257 + offsetY * 2,100,42,buyAllow);
////        if(stone == 5)
////        {
////            connect(attributeGroup[2],SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
////            connect(attributeGroup[2],SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
////        }
////        if(stone == 4)
////        {
////            buy[0] = true;
////            buy[1] = true;
////            if(storeData->gameCharacter[5]->characterNum == 12)
////            {
////                buy[1] = false;
////            }
////        }
////        if(stone < 4)
////        {
////            buy[2] = true;
////            if(storeData->gameCharacter[5]->characterNum == 12)
////            {
////                buy[2] = false;
////                buy[3] = true;
////            }
////        }
////        if(storeData->gameCharacter[5]->cardLimit - storeData->gameCharacter[5]->cardNum < 3)
////        {
////            for(int i = 0;i < 4;i++)
////            {
////                buyGroup[i] = false;
////            }
////        }
////        if(!buyAllow)
////        {
////            for(int i = 0;i < 4;i++)
////            {
////                buy[i] = false;
////            }
////        }
////        buyGroup[0] = new PicButton(43,9 + 328 + 100 + offsetX * 2,257 + offsetY * 2,50,42,buy[0]);
////        buyGroup[1] = new PicButton(44,9 + 328 + 100 + 50 + offsetX * 3,257 + offsetY * 2,50,42,buy[1]);
////        buyGroup[2] = new PicButton(41,9 + 328 + 100 + 50 * 2 + offsetX * 4,257 + offsetY * 2,100,42,buy[2]);
////        buyGroup[3] = new PicButton(46,9 + 328 + 100 * 2 + 50 * 2 + offsetX * 5,257 + offsetY * 2,100,42,buy[3]);
////        bool composeAllow = false;
////        if(color)
////        {
////            if((storeData->crystalBlue + storeData->gemBlue > 2) && (storeData->gameCharacter[5]->cardLimit - storeData->gameCharacter[5]->cardNum > 2))
////            {
////                composeAllow = true;
////            }
////        }
////        else
////        {
////            if((storeData->crystalRed + storeData->gemRed > 2) && (storeData->gameCharacter[5]->cardLimit - storeData->gameCharacter[5]->cardNum > 2))
////            {
////                composeAllow = true;
////            }
////        }
////        bool compose[4];
////        for(int i = 0;i < 4;i++)
////        {
////            compose[i] = false;
////        }
////        int fixCrystal;
////        if(color)
////        {
////            stone = storeData->gemBlue;
////            fixCrystal = storeData->crystalBlue;
////        }
////        else
////        {
////            stone = storeData->gemRed;
////            fixCrystal = storeData->crystalRed;
////        }
////        if(stone > 2)
////        {
////            compose[2] = true;
////        }
////        if(stone > 1 && fixCrystal > 0)
////        {
////            compose[1] = true;
////        }
////        if(stone > 0 && fixCrystal > 1)
////        {
////            compose[0] = true;
////        }
////        if(fixCrystal > 2)
////        {
////            compose[3] = true;
////        }
////        if(storeData->gameCharacter[5]->cardLimit - storeData->gameCharacter[5]->cardNum < 3)
////        {
////            for(int i = 0;i < 4;i++)
////            {
////                compose[i] = false;
////            }
////        }
////        if(color)
////        {
////            stone = storeData->gemBlue + storeData->crystalBlue;
////        }
////        else
////        {
////            stone = storeData->gemRed + storeData->crystalRed;
////        }
////        if(stone < 3)
////        {
////            for(int i = 0;i < 3;i++)
////            {
////                compose[i] = false;
////            }
////        }
////        attributeGroup[3] = new PicButton(37,9 + 328 + offsetX,257 + offsetY * 3,100,42,composeAllow);
////        if(!composeAllow)
////        {
////            for(int i = 0;i < 3;i++)
////            {
////                compose[i] = false;
////            }
////        }
////        composeGroup[0] = new PicButton(43,9 + 328 + 100 + offsetX * 2,257 + offsetY * 3,50,42,compose[0]);
////        composeGroup[1] = new PicButton(46,9 + 328 + 100 + 50 + offsetX * 3,257 + offsetY * 3,100,42,compose[1]);
////        composeGroup[2] = new PicButton(47,9 + 328 + 100 * 2 + 50 + offsetX * 4,257 +offsetY * 3,100,42,compose[2]);
////        composeGroup[3] = new PicButton(44,9 + 328 + 100 * 3 + 50 + offsetX * 5,257 + offsetY * 3,50,42,compose[3]);
////        for(int i = 0;i < actNum;i ++)
////        {
////            connect(activateGroup[i],SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
////            connect(storeWindow,SIGNAL(mouseClicked(int,int)),activateGroup[i],SLOT(isThisClicked(int,int)));
////        }
////        for(int i = 0;i < 5;i++)
////        {
////            connect(refineGroup[i],SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
////            connect(storeWindow,SIGNAL(mouseClicked(int,int)),refineGroup[i],SLOT(isThisClicked(int,int)));
////        }
////        for(int i = 0;i < 4;i++)
////        {
////            connect(buyGroup[i],SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
////            connect(storeWindow,SIGNAL(mouseClicked(int,int)),buyGroup[i],SLOT(isThisClicked(int,int)));
////        }
////        for(int i = 0;i < 4;i++)
////        {
////            connect(composeGroup[i],SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
////            connect(storeWindow,SIGNAL(mouseClicked(int,int)),composeGroup[i],SLOT(isThisClicked(int,int)));
////        }
////        for(int i = 0;i < 4;i++)
////        {
////            connect(attributeGroup[i],SIGNAL(changeClicked()),ensure,SLOT(cancelClick()));
////        }
////        if(stone > 2)
////        {
////            if(color)
////            {
////                stone = storeData->gemBlue;
////            }
////            else
////            {
////                stone = storeData->gemRed;
////            }
////        }
////        for(int i = 0; i < 4;i++)
////        {
////            connect(storeWindow,SIGNAL(mouseClicked(int,int)),attributeGroup[i],SLOT(isThisClicked(int,int)));
////            for(int j = 0;j < 4;j++)
////            {
////                if(i != j)
////                {
////                    connect(attributeGroup[i],SIGNAL(changeClicked()),attributeGroup[j],SLOT(cancelX()));
////                }
////                for(int k = 0;k < actNum;k++)
////                {
////                    if(i != 0)
////                    {
////                        connect(attributeGroup[i],SIGNAL(changeClicked()),activateGroup[k],SLOT(cancelX()));
////                    }
////                }
////                for(int k = 0;k < 5;k ++)
////                {
////                    if(i != 1)
////                    {
////                        connect(attributeGroup[i],SIGNAL(changeClicked()),refineGroup[k],SLOT(cancelX()));
////                    }
////                }
////                for(int k = 0;k < 4;k++)
////                {
////                    if(i != 2)
////                    {
////                        connect(attributeGroup[i],SIGNAL(changeClicked()),buyGroup[k],SLOT(cancelX()));
////                    }
////                }
////                for(int k = 0;k < 4;k++)
////                {
////                    if(i != 3)
////                    {
////                        connect(attributeGroup[i],SIGNAL(changeClicked()),composeGroup[k],SLOT(cancelX()));
////                    }
////                }
////            }
////            connect(attributeGroup[i],SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
////        }
////        for(int i = 0;i < actNum;i++)
////        {
////            connect(activateGroup[i],SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
////            for(int j = 0;j < 4;j++)
////            {
////                if(j == 0)
////                {
////                    connect(activateGroup[i],SIGNAL(changeClicked()),attributeGroup[j],SLOT(recover()));
////                }
////                else
////                {
////                    connect(activateGroup[i],SIGNAL(changeClicked()),attributeGroup[j],SLOT(cancelX()));
////                }
////            }
////            for(int j = 0;j < actNum;j++)
////            {
////                if(i != j)
////                {
////                    connect(activateGroup[i],SIGNAL(changeClicked()),activateGroup[j],SLOT(cancelX()));
////                }
////            }
////            for(int j = 0;j < 5;j++)
////            {
////                connect(activateGroup[i],SIGNAL(changeClicked()),refineGroup[j],SLOT(cancelX()));
////            }
////            for(int j = 0;j < 4;j++)
////            {
////                connect(activateGroup[i],SIGNAL(changeClicked()),buyGroup[j],SLOT(cancelX()));
////                connect(activateGroup[i],SIGNAL(changeClicked()),composeGroup[j],SLOT(cancelX()));
////            }
////        }
////        for(int i = 0;i < 5;i++)
////        {
////            connect(refineGroup[i],SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
////            for(int j = 0;j < 4;j++)
////            {
////                if(j == 1)
////                {
////                    connect(refineGroup[i],SIGNAL(changeClicked()),attributeGroup[j],SLOT(recover()));
////                }
////                else
////                {
////                    connect(refineGroup[i],SIGNAL(changeClicked()),attributeGroup[j],SLOT(cancelX()));
////                }
////            }
////            for(int j = 0;j < 5;j++)
////            {
////                if(i != j)
////                {
////                    connect(refineGroup[i],SIGNAL(changeClicked()),refineGroup[j],SLOT(cancelX()));
////                }
////            }
////            for(int j = 0;j < 4;j++)
////            {
////                connect(refineGroup[i],SIGNAL(changeClicked()),buyGroup[j],SLOT(cancelX()));
////                connect(refineGroup[i],SIGNAL(changeClicked()),composeGroup[j],SLOT(cancelX()));
////            }
////            for(int j = 0;j < actNum;j++)
////            {
////                connect(refineGroup[i],SIGNAL(changeClicked()),activateGroup[j],SLOT(cancelX()));
////            }
////        }
////        for(int i = 0;i < 4;i++)
////        {
////            connect(buyGroup[i],SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
////            for(int j = 0;j < 4;j++)
////            {
////                if(j == 2)
////                {
////                    connect(buyGroup[i],SIGNAL(changeClicked()),attributeGroup[j],SLOT(recover()));
////                }
////                else
////                {
////                    connect(buyGroup[i],SIGNAL(changeClicked()),attributeGroup[j],SLOT(cancelX()));
////                }
////            }
////            for(int j = 0;j < 5;j++)
////            {
////                connect(buyGroup[i],SIGNAL(changeClicked()),refineGroup[j],SLOT(cancelX()));
////            }
////            for(int j = 0;j < 4;j++)
////            {
////                if(i != j)
////                {
////                    connect(buyGroup[i],SIGNAL(changeClicked()),buyGroup[j],SLOT(cancelX()));
////                }
////                connect(buyGroup[i],SIGNAL(changeClicked()),composeGroup[j],SLOT(cancelX()));
////            }
////            for(int j = 0;j < actNum;j++)
////            {
////                connect(buyGroup[i],SIGNAL(changeClicked()),activateGroup[j],SLOT(cancelX()));
////            }
////        }
////        for(int i = 0;i < 4;i++)
////        {
////            connect(composeGroup[i],SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
////            for(int j = 0;j < 4;j++)
////            {
////                if(j == 3)
////                {
////                    connect(composeGroup[i],SIGNAL(changeClicked()),attributeGroup[j],SLOT(recover()));
////                }
////                else
////                {
////                    connect(composeGroup[i],SIGNAL(changeClicked()),attributeGroup[j],SLOT(cancelX()));
////                }
////            }
////            for(int j = 0;j < 5;j++)
////            {
////                connect(composeGroup[i],SIGNAL(changeClicked()),refineGroup[j],SLOT(cancelX()));
////            }
////            for(int j = 0;j < 4;j++)
////            {
////                if(i != j)
////                {
////                    connect(composeGroup[i],SIGNAL(changeClicked()),composeGroup[j],SLOT(cancelX()));
////                }
////                connect(composeGroup[i],SIGNAL(changeClicked()),buyGroup[j],SLOT(cancelX()));
////            }
////            for(int j = 0;j < actNum;j++)
////            {
////                connect(composeGroup[i],SIGNAL(changeClicked()),activateGroup[j],SLOT(cancelX()));
////            }
////        }
////        if(paintStruct->gameCharacter[5]->characterNum == 12)
////        {
////            attributeGroup[1]->setCheckable(false);
////            for(int i = 0;i < 5;i++)
////            {
////                refineGroup[i]->setCheckable(false);
////            }
////            for(int j = 0;j < 6;j++)
////            {
////                if(paintStruct->gameCharacter[j]->color == paintStruct->gameCharacter[5]->color)
////                {
////                    paintStruct->gameCharacter[j]->characterPic->setCheckable(true);
////                    connect(paintStruct->gameCharacter[j]->characterPic,SIGNAL(changeClicked()),this,SLOT(adventureRefine()));
////                    connect(paintStruct->gameCharacter[j]->characterPic,SIGNAL(notClicked()),this,SLOT(adventureReset()));
////                }
////                for(int k = 0;k < 6;k++)
////                {
////                    if(j != k)
////                    {
////                        connect(paintStruct->gameCharacter[j]->characterPic,SIGNAL(changeClicked()),paintStruct->gameCharacter[k]->characterPic,SLOT(cancelX()));
////                    }
////                }
////            }
////        }
////    }
////    if(kind[0] == 2)
////    {
////        connect(storeWindow,SIGNAL(mouseClicked(int,int)),ensure,SLOT(isThisClicked(int,int)));
////        connect(storeWindow,SIGNAL(mouseClicked(int,int)),cancel,SLOT(isThisClicked(int,int)));
////        //system("pause");
////        for(int i = 0;i < 5;i++)
////        {
////            if(i < storeData->gameCharacter[5]->cure && i < information[1])
////            {
////                number[i] = new PicButton(i + 49,99 + 328 + 70 * i,407,50,50,true);
////            }
////            else
////            {
////                number[i] = new PicButton(i + 49,99 + 328 + 70 * i,407,50,50,false);
////            }
////            connect(storeWindow,SIGNAL(mouseClicked(int,int)),number[i],SLOT(isThisClicked(int,int)));
////            connect(number[i],SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
////            connect(number[i],SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
////        }
////        for(int i = 0;i < 5;i++)
////        {
////            for(int j = 0;j < 5;j++)
////            {
////                if(i != j)
////                {
////                    connect(number[i],SIGNAL(changeClicked()),number[j],SLOT(cancelX()));
////                }
////            }
////        }
////        if(paintStruct->gameCharacter[5]->characterNum == 15)
////        {
////            for(int i = 1;i < 5;i++)
////            {
////                number[i]->setCheckable(false);
////            }
////        }
////    }
//    //font->setPointSize();
//}
//}

//void AskDialog::paint(QPaintEvent* event, QPainter* painter)
//{
//    painter->drawPixmap(328,247,bg->width(),bg->height(),*bg);
//    ensure->paint(event,painter);
//    cancel->paint(event,painter);
//    switch(kind[0])
//    {
//        case 0:
//        {
//             break;
//        }
//        case 1:
//        {
//            for(int i = 0;i < actNum;i++)
//            {
//                activateGroup[i]->paint(event,painter);
//            }
//            for(int i = 0;i < 4;i++)
//            {
//                attributeGroup[i]->paint(event,painter);
//            }
//            for(int i = 0;i < 5;i++)
//            {
//                refineGroup[i]->paint(event,painter);
//            }
//            for(int i = 0;i < 4;i++)
//            {
//                buyGroup[i]->paint(event,painter);
//            }
//            for(int i = 0;i < 4;i++)
//            {
//                composeGroup[i]->paint(event,painter);
//            }
//            break;
//        }
//        case 2:
//        {
//            QString* s;
//            //s = new QString(QString::fromUtf8("取消接三张牌."));
//            s = new QString(QString::fromUtf8("请选择治疗,伤害:"));
//            labelOne->setText(*s);
//            labelOne->setFont(*font);
//            labelOne->setPalette(*palette);
//            labelOne->move(328 + 25,247 + 20);
//            labelOne->show();
//            s->sprintf("%d",kind[1]);
//            labelTwo->setText(*s);
//            labelTwo->setFont(*font);
//            labelTwo->setPalette(*palette);
//            labelTwo->move(328 + 25,247 + 60);
//            labelTwo->show();
//            for(int i = 0;i < 5;i++)
//            {
//                number[i]->paint(event,painter);
//            }
//            break;
//        }
//    }
//}
    //void AskDialog::sendMessageSpe()
    //{
    //    std::vector<int> tempMes;
    //    if(cancel->isChecked())
    //    {
    //        tempMes.push_back(0);
    //        emit sendMessageSpeSig(tempMes);
    //        return;
    //    }
    //    else
    //    {
    //        if(attributeGroup[0]->isChecked())
    //        {
    //            tempMes.push_back(1);
    //            for(int i = 0;i < actNum;i++)
    //            {
    //                if(activateGroup[i]->isChecked())
    //                {
    //                    tempMes.push_back(i);
    //                    emit sendMessageSpeSig(tempMes);
    //                    return;
    //                }
    //            }
    //        }
    //        if(attributeGroup[1]->isChecked())
    //        {
    //            tempMes.push_back(2);
    //            if(refineGroup[0]->isChecked())
    //            {
    //                tempMes.push_back(1);
    //                tempMes.push_back(0);
    //            }
    //            if(refineGroup[1]->isChecked())
    //            {
    //                tempMes.push_back(0);
    //                tempMes.push_back(1);
    //            }
    //            if(refineGroup[2]->isChecked())
    //            {
    //                tempMes.push_back(2);
    //                tempMes.push_back(0);
    //            }
    //            if(refineGroup[3]->isChecked())
    //            {
    //                tempMes.push_back(1);
    //                tempMes.push_back(1);
    //            }
    //            if(refineGroup[4]->isChecked())
    //            {
    //                tempMes.push_back(0);
    //                tempMes.push_back(2);
    //            }
    //            if(storeData->gameCharacter[5]->characterNum == 12)
    //            {
    //                for(int i = 0;i < 6;i++)
    //                {
    //                    if(storeData->gameCharacter[i]->characterPic->isChecked())
    //                    {
    //                        int site = (-i + storeData->yourSite + 5) % 6;
    //                        tempMes.push_back(site);
    //                        emit sendMessageSpeSig(tempMes);
    //                        return;
    //                    }
    //                }
    //            }
    //            emit sendMessageSpeSig(tempMes);
    //            return;
    //        }
    //        if(attributeGroup[2]->isChecked())
    //        {
    //            tempMes.push_back(3);
    //            if(buyGroup[0]->isChecked())
    //            {
    //                tempMes.push_back(1);
    //                tempMes.push_back(0);
    //            }
    //            if(buyGroup[1]->isChecked())
    //            {
    //                tempMes.push_back(0);
    //                tempMes.push_back(1);
    //            }
    //            if(buyGroup[2]->isChecked())
    //            {
    //                tempMes.push_back(1);
    //                tempMes.push_back(1);
    //            }
    //            if(buyGroup[3]->isChecked())
    //            {
    //                tempMes.push_back(2);
    //                tempMes.push_back(0);
    //            }
    //            emit sendMessageSpeSig(tempMes);
    //            return;
    //        }
    //        if(attributeGroup[3]->isChecked())
    //        {
    //            tempMes.push_back(4);
    //            if(composeGroup[0]->isChecked())
    //            {
    //                tempMes.push_back(1);
    //                tempMes.push_back(2);
    //            }
    //            if(composeGroup[1]->isChecked())
    //            {
    //                tempMes.push_back(2);
    //                tempMes.push_back(1);
    //            }
    //            if(composeGroup[2]->isChecked())
    //            {
    //                tempMes.push_back(3);
    //                tempMes.push_back(0);
    //            }
    //            if(composeGroup[3]->isChecked())
    //            {
    //                tempMes.push_back(0);
    //                tempMes.push_back(3);
    //            }
    //            emit sendMessageSpeSig(tempMes);
    //            return;
    //        }
    //    }
    //}
    //void AskDialog::sendMessageWeak()
    //{
    //    std::vector<int> tempMes;
    //    if(ensure->isChecked())
    //    {
    //        tempMes.push_back(0);
    //    }
    //    else
    //    {
    //        tempMes.push_back(1);
    //    }
    //    emit sendMessageWeakSig(tempMes);
    //}
    //void AskDialog::sendMessageCure()
    //{
    //    std::vector<int> tempMes;
    //    if(cancel->isChecked())
    //    {
    //        tempMes.push_back(0);
    //        emit sendMessageCureSig(tempMes);
    //        return;
    //    }
    //    for(int i = 0;i < 5;i++)
    //    {
    //        if(number[i]->isChecked())
    //        {
    //            tempMes.push_back(i + 1);
    //            emit sendMessageCureSig(tempMes);
    //            return;
    //        }
    //    }
    //}
    //void AskDialog::sendMessageAskDialog()
    //{
    //    switch(informationKind)
    //    {
    //        case 4:
    //        {
    //            sendMessageWeak();
    //            break;
    //        }
    //        case 6:
    //        {
    //            sendMessageSpe();
    //            break;
    //        }
    //        case 12:
    //        {
    //            sendMessageCure();
    //            break;
    //        }
    //    }
    //}
}

//void AskDialog::destroyLabel()
//{
//    delete labelOne;
//    delete labelTwo;
//}


//int AskDialog::adventureRefine()
//{
//    for(int i = 0;i < 6;i++)
//    {
//        if(storeData->gameCharacter[i]->characterPic->isChecked())
//        {
//            bool adRefine[5];
//            bool refineAllow = false;
//            int color = storeData->gameCharacter[5]->color;
//            int stone = 0;
//            if(color)
//            {
//                stone = storeData->crystalBlue + storeData->gemBlue;
//            }
//            else
//            {
//                stone = storeData->crystalRed + storeData->gemRed;
//            }
//            if(stone && (storeData->gameCharacter[i]->gem + storeData->gameCharacter[i]->crystal != storeData->gameCharacter[i]->energeLimit))
//            {
//                refineAllow = true;
//                attributeGroup[1]->canBeClicked = refineAllow;
//            }
//            int crystalExist = 0;
//            int gemExist = 0;
//            if(color)
//            {
//                crystalExist = storeData->crystalBlue;
//                gemExist = storeData->gemBlue;
//            }
//            else
//            {
//                crystalExist = storeData->crystalRed;
//                gemExist = storeData->gemRed;
//            }
//            for(int j = 0;j < 5;j++)
//            {
//                adRefine[j] = false;
//            }
//            if(!crystalExist && !gemExist)
//            {
//            }
//            if(!crystalExist && gemExist == 1)
//            {
//                adRefine[0] = true;
//            }
//            if(!gemExist && crystalExist == 1)
//            {
//                adRefine[1] = true;
//            }
//            if(!crystalExist && gemExist > 1)
//            {
//                adRefine[0] = true;
//                adRefine[2] = true;
//            }
//            if(!gemExist && crystalExist > 1)
//            {
//                adRefine[1] = true;
//                adRefine[4] = true;
//            }
//            if(gemExist == 1 && crystalExist == 1)
//            {
//                adRefine[0] = true;
//                adRefine[1] = true;
//                adRefine[3] = true;
//            }
//            if(gemExist > 1 && crystalExist == 1)
//            {
//                adRefine[0] = true;
//                adRefine[1] = true;
//                adRefine[2] = true;
//                adRefine[3] = true;
//            }
//            if(gemExist == 1 && crystalExist > 1)
//            {
//                adRefine[0] = true;
//                adRefine[1] = true;
//                adRefine[3] = true;
//                adRefine[4] = true;
//            }
//            if(gemExist > 1 && crystalExist > 1)
//            {
//                for(int j = 0;j < 5;j++)
//                {
//                    adRefine[j] = true;
//                }
//            }
//            stone = storeData->gameCharacter[i]->crystal + storeData->gameCharacter[i]->gem;
//            if(storeData->gameCharacter[i]->energeLimit == stone)
//            {
//                for(int j = 0;j < 5;j++)
//                {
//                    adRefine[j] = false;
//                }
//            }
//            if(storeData->gameCharacter[5]->energeLimit == stone + 1)
//            {
//                for(int j = 2;j < 5;j++)
//                {
//                    adRefine[j] = false;
//                }
//            }
//            if(!refineAllow)
//            {
//                for(int j = 0;j < 5;j++)
//                {
//                    adRefine[j] = false;
//                }
//            }
//            for(int j = 0;j < 5;j++)
//            {
//                refineGroup[j]->canBeClicked = adRefine[j];
//            }
//            break;
//        }
//    }
//}
//void AskDialog::adventureReset()
//{
//    for(int i = 0;i < 5;i++)
//    {
//        refineGroup[i]->setCheckable(false);
//    }
//    attributeGroup[1]->setCheckable(false);
//}


