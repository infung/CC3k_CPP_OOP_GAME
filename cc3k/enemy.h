#ifndef ENEMY_H
#define ENEMY_H
struct Info;
#include "subject.h"
#include "enemy.h"
#include "observer.h"
#include "character.h"
class Player;
class Enemy: public Character, public Observer{
public:
	Enemy(int hp, int atk, int def, char c);
	virtual void notify(Subject &who);
	virtual void attack(Player * player);
	virtual int acceptAttack(Player * player);
	virtual void dieTo(Player * player);
	virtual void moveTo(int x, int y);
	SubscriptionType subType() const;
};

#endif

