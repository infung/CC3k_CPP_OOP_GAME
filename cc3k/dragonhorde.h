#ifndef _DRAGONHORDE_H_
#define _DRAGONHORDE_H_
#include "treasure.h"

class DragonHorde : public Treasure {
	bool isLocked;
public:
	DragonHorde(int val);
	void usedBy(Player * player) override;
	~DragonHorde();
	friend class Dragon;
};

#endif

