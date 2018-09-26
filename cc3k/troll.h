#ifndef __TROLL_H__
#define __TROLL_H__
#include "player.h"
#include "info.h"

class Troll : public Player {

public:
	Troll();
	~Troll();
	void attack(std::shared_ptr<Enemy> e) override;
	void move(std::string dir) override;

};

#endif

