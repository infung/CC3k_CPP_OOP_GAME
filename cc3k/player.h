#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "character.h"
#include "potion.h"
#include "treasure.h"
#include "event.h"
#include <cmath>

class Enemy;
class Item;


class Player : public Character {

	int gold;
	int maxHp;
	char race;
	Event eventLog;

public:
	Player (int hp, int atk, int def, int maxHp, char race);
	virtual ~Player();
	
 	int calculateDamage(int att, int def) const;
	virtual void attack(std::shared_ptr<Enemy> e);
	virtual void acceptAttack(Enemy * e);
	int getmaxHp() const;
	virtual void useItem(std::shared_ptr<Treasure> item);
	virtual void useItem(std::shared_ptr<Potion> item);
	void addGold(int val); 
	int getGold() const;
	char getRace();
	void log(std::string str); // logs information to 'eventLog' object
	void printLog();
};

#endif

