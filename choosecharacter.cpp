#include "choosecharacter.h"

ChooseCharacter::ChooseCharacter(int numOne,int numTwo,int numThree,QWidget *parent) :
    QLabel(parent)
{
    setPixmap(QPixmap(":/character/chooseCharacterFrame"));
    setGeometry(328,247, 520, 280);


    character[0] = new CharacterButton(numOne,28,23,this);
    character[1] = new CharacterButton(numTwo,187,23,this);
    character[2] = new CharacterButton(numThree,346,23,this);
    for(int i = 0; i<3; i++) characters.addButton(character[i],i);
    characters.setExclusive(true);
    ensure = new PicButton(32,595-328,233,100,42,false,this);
    cancel = new PicButton(33,715-328,233,100,42,false,this);
    connect(cancel,SIGNAL(clicked()),this,SLOT(recover()));
    connect(&characters,SIGNAL(buttonClicked(int)),ensure,SLOT(setCheckableTrue()));
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
