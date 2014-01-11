//
//  placeinfo.h
//  AsteriatedGUI
//
//  Created by Hubert on 14-1-9.
//
//

#ifndef PLACEINFO_H
#define PLACEINFO_H
//define all place information here
#define GEO_SCREEN_W 1366
#define GEO_SCREEN_H 768
#define GEO_CHARACTER_W 157//+18
#define GEO_CHARACTER_H 223//+18
const int GEO_CHARACTER_X[6]={124,264,509,754,894,194};
const int GEO_CHARACTER_XOFFSET[6]={0,18,18,18,18,18};
const int GEO_CHARACTER_Y[6]={273,6,6,6,273,541};
const int GEO_CHARACTER_YOFFSET[6]={18,0,0,0,18,18};
const int GEO_CHARACTER_ATTRIBUTE_X[6]= {157-18,-18,-18,-18,-18,-18};
const int GEO_CHARACTER_ATTRIBUTE_Y[6]= {20,20,20,20,20,20};
const int GEO_CHARACTER_CURE_X[6]= {62,62,62,62,62,62};
const int GEO_CHARACTER_CURE_Y[6]= {-18,223-18,223-18,223-18,-18,-18};
const int GEO_CHARACTER_GEM_X[6]= {0,0,0,0,0,0};
const int GEO_CHARACTER_GEM_Y[6]= {-18,223-18,223-18,223-18,-18,-18};
const int GEO_CHARACTER_CRYSTAL_X[6]= {31,31,31,31,31,31};
const int GEO_CHARACTER_CRYSTAL_Y[6]= {-18,223-18,223-18,223-18,-18,-18};
const int GEO_CHARACTER_BSOUL_X[6]= {93,93,93,93,93,93};
const int GEO_CHARACTER_BSOUL_Y[6]= {-18,223-18,223-18,223-18,-18,-18};
const int GEO_CHARACTER_YSOUL_X[6]= {124,124,124,124,124,124};
const int GEO_CHARACTER_YSOUL_Y[6]= {-18,223-18,223-18,223-18,-18,-18};
#define GEO_CHARACTER_NUMBER_X 100
#define GEO_CHARACTER_NUMBER_Y 133
#define GEO_CHARACTER_ATTRIBUTE_YOFFSET 36
#define GEO_CHARACTER_ATTRIBUTE_SIZE 36
#define GEO_CARD_W 102
#define GEO_CARD_H 143
#define GEO_CARD_Y 611

#define GEO_MORALE_W 50
#define GEO_MORALE_H 50
#define GEO_MORALE_X 39
#define GEO_MORALE_RED_Y 321
#define GEO_MORALE_BLUE_Y 392

#define GEO_GRAIL_W 50
#define GEO_GRAIL_H 50
#define GEO_GRAIL_X 15
#define GEO_GRAIL_RED_Y 67
#define GEO_GRAIL_BLUE_Y 443
#define GEO_GRAIL_YOFFSET 52

#define GEO_STONE_W 50
#define GEO_STONE_H 50
#define GEO_STONE_X 15 + 46
#define GEO_STONE_RED_Y 67
#define GEO_STONE_BLUE_Y 443
#define GEO_STONE_YOFFSET 52

#define GEO_DIALOG_X 328
#define GEO_DIALOG_Y 247
#define GEO_DIALOG_H 280
#define GEO_DIALOG_W 520
#define GEO_DIALOG_ENSURE_X 267 
//595-328
#define GEO_DIALOG_ENSURE_Y 232 
//479-247
#define GEO_DIALOG_ENSURE_H 42
#define GEO_DIALOG_ENSURE_W 100
#define GEO_DIALOG_CANCEL_X (715-328)
#define GEO_DIALOG_CANCEL_Y (479-247)
#define GEO_DIALOG_CANCEL_H 42
#define GEO_DIALOG_CANCEL_W 100
#endif
//if(i == 0 || i == 4)
//{
//    SoulYX[i] = gameCharacter[i]->xp + 66;
//    SoulBX[i] = gameCharacter[i]->xp + 103 ;
//    SoulYY[i] = gameCharacter[i]->yp + 223 + 2 - 18;
//    SoulBY[i] = gameCharacter[i]->yp + 223 + 2 - 18;
//}
//int offsetYQUQ = 50;
//if(i == 1)
//{
//    SoulYX[i] = gameCharacter[i]->xp + 157 + 2 - 18;
//    SoulBX[i] = gameCharacter[i]->xp + 157 + 2 - 18;
//    SoulYY[i] = gameCharacter[i]->yp + offsetYQUQ * 2;
//    SoulBY[i] = gameCharacter[i]->yp + offsetYQUQ * 3;
//}
//if(i == 2 || i == 3)
//{
//    SoulYX[i] = gameCharacter[i]->xp - 2 - 18;
//    SoulBX[i] = gameCharacter[i]->xp - 2 - 18;
//    SoulYY[i] = gameCharacter[i]->yp + offsetYQUQ * 2;
//    SoulBY[i] = gameCharacter[i]->yp + offsetYQUQ * 3;
//}
//if(i == 5)
//{
//    SoulYX[i] = gameCharacter[i]->xp + 157 + 4 + 66;
//    SoulBX[i] = gameCharacter[i]->xp + 157 + 4 + 103;
//    SoulYY[i] = gameCharacter[i]->yp - 2 - 20;
//    SoulBY[i] = gameCharacter[i]->yp - 2 - 20;
//}
