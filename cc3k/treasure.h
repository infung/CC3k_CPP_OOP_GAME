#ifndef _TREASURE_H_
#define _TREASURE_H_
#include "item.h"
#include "info.h"
#include "observer.h"
#include "subscriptiontype.h"
class Player;

class Treasure : public Item, public Observer{
	int gold;
public:
	int getGold();
	Treasure(int value);
	virtual void usedBy(Player * player);
	Info getInfo() const;
	SubscriptionType subType() const;
	void notify(Subject & who);
	virtual ~Treasure();
};

#endif

