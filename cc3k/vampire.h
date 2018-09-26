#ifndef __VAMPIRE_H__
#define __VAMPIRE_H__
#include "player.h"
#include "info.h"

class Vampire : public Player {

public:
	Vampire();
	~Vampire();
	void attack(std::shared_ptr<Enemy> e);

};
#endif


