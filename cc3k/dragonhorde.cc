#include "dragonhorde.h"
#include "player.h"
using namespace std;

DragonHorde::DragonHorde(int val) : Treasure{val}, isLocked{true} {}

void DragonHorde::usedBy(Player * player) {
	if(!isLocked) {
		player->addGold(getGold());
	}
}

DragonHorde::~DragonHorde() {}

