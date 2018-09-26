#ifndef HALFLING_H
#define HALFLING_H
#include "info.h"
#include "subject.h"
#include "enemy.h"
#include "observer.h"

class Halfling: public Enemy{
public:
	Halfling();
	int acceptAttack(Player * player);
};

#endif

