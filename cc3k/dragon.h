#ifndef DRAGON_H
#define DRAGON_H
class Subject;
#include "dragonhorde.h"
#include "enemy.h"
#include "observer.h"
class Player;
class Dragon: public Enemy{
private:
	
public:
	std::shared_ptr<DragonHorde> dh;

	Dragon(std::shared_ptr<DragonHorde> dh);

	void notify(Subject &who) override;
	void dieTo(Player * player) override;
	void moveTo(int x, int y) override;
};

#endif

