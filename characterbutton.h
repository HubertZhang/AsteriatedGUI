//
//  characterbutton.h
//  AsteriatedGUI
//
//  Created by Hubert on 14-1-9.
//
//

#ifndef CHARACTERBUTTON_H
#define CHARACTERBUTTON_H
#include "picbutton.h"
#include "placeinfo.h"
class CharacterButton : public PicButton
{
    int character;
public:
    explicit CharacterButton(int character, int place, QWidget* parent);
    int getCharacter;
};

#endif /* defined(CHARACTERBUTTON_H) */
