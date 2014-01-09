#ifndef CARDLIST_H
#define CARDLIST_H

#include "card.h"
class CardList
{
private:
    Card *cardList;
    void initCardList();
public:
    CardList();
    int getName(int cardNum);
    int getType(int cardNum);
    int getKind(int cardNum);
    int getSkillOne(int cardNum);
    int getSkillTwo(int cardNum);
    int getNature(int cardNum);
};
CardList cardlist;
#endif // CARDLIST_H
