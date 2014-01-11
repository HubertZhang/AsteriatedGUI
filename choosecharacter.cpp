#include "choosecharacter.h"

ChooseCharacter::ChooseCharacter(int numOne,int numTwo,int numThree,QWidget *parent) :
    QLabel(parent)
{
    setPixmap(QPixmap(":/character/chooseCharacterFrame"));
    setGeometry(328,247, 520, 280);
    character[0] = new CharacterButton(numOne,28,23,this);
    character[1] = new CharacterButton(numTwo,187,23,this);
    character[2] = new CharacterButton(numThree,346,23,this);
    ensure = new PicButton(33,595-328,233,100,42,false,this);
    cancel = new PicButton(34,715-328,233,100,42,false,this);
    connect(cancel,SIGNAL(clicked()),this,SLOT(recover()));
    for(int i = 0;i < 3;i++)
    {
        connect(character[i],SIGNAL(beChecked()),character[(i + 1) % 3],SLOT(disable()));
        connect(character[i],SIGNAL(beChecked()),character[(i + 2) % 3],SLOT(disable()));
        connect(character[i],SIGNAL(unChecked()),character[(i + 1) % 3],SLOT(enable()));
        connect(character[i],SIGNAL(unChecked()),character[(i + 2) % 3],SLOT(enable()));
        connect(character[i],SIGNAL(beChecked()),ensure,SLOT(enable()));
        connect(character[i],SIGNAL(unChecked()),ensure,SLOT(disable()));
        connect(character[i],SIGNAL(beChecked()),cancel,SLOT(enable()));
    }
    connect(ensure,SIGNAL(clicked()),this,SLOT(sendMessage()));
    show();
}

void ChooseCharacter::recover()
{
    for (int i = 0; i<3; i++)
    {
        character[i]->setChecked(false);
        character[i]->setCheckable(true);
    }

    ensure->setCheckable(false);
}

void ChooseCharacter::sendMessage()
{
    std::vector<int> tempMes;
    for(int i = 0;i < 3;i++)
    {
        if(character[i]->isChecked())
        {
            tempMes.push_back(character[i]->getCharacter());
            break;
        }
    }
    emit sendMessageChooseSig(tempMes);
    this->~ChooseCharacter();
}
