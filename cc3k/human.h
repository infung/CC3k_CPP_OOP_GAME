#ifndef HUMAN_H
#define HUMAN_H
#include "info.h"
#include "subject.h"
#include "enemy.h"
#include "observer.h"

class Human: public Enemy{
public:
	Human();
	void dieTo(Player * player) override;
};

#endif

