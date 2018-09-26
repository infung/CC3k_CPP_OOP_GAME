#ifndef MERCHANT_H
#define MRECHANT_H
#include "info.h"
#include "subject.h"
#include "enemy.h"
#include "observer.h"

class Merchant: public Enemy{
private:
	static bool isHostile;
public:	
	Merchant();
	void setHostile();
	void notify(Subject &who) override;
	void dieTo(Player * player) override;
};

#endif

