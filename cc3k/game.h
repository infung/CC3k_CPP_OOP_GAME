#ifndef __GAME_H__
#define __GAME_H__
#include "player.h"
#include "floor.h"
#include "potion.h"
#include "drow.h"
#include "vampire.h"
#include "shade.h"
#include "goblin.h"
#include "troll.h"
#include <vector>
class  Game {
	int currLevel;
	std::shared_ptr<Player> player;
	std::vector<std::shared_ptr<Floor>> floors;
	bool enemyMove = true;
	int getScore();
public:
	 Game();
	 ~Game();
	 void init(char race);
	 void generateFloor();
	 void freeze();
	 void quit();
	 void restart();
	 bool isLost();
	 bool isWon();
	 void moveToNext();
	 void playerMove(std::string dir);
	 void playerAttack(std::string dir);
	 void usePotion(std::string dir);
	// friend Floor;

};

#endif


