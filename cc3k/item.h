#ifndef _ITEM_H_
#define _ITEM_H_
#include "subject.h"
#include "subscriptiontype.h"
class Player;

class Item : public Subject{
	
public:
	Item(char display);
	virtual void usedBy(Player * player) = 0;
	SubscriptionType subType();
	virtual ~Item() = 0;
};
#endif


