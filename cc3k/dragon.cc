#include "dragon.h"
#include "info.h"
#include "player.h"
#include "character.h"
#include "item.h"
#include <iostream>
#include <sstream>
using namespace std;

Dragon::Dragon(shared_ptr<DragonHorde> dh)
	:Enemy{150, 20, 20, 'D'}, dh{dh} {}

void Dragon::notify(Subject &who){
	if(((who.getInfo().x - this -> getX() <= 1 &&
		who.getInfo().x - this -> getX() >= -1 ) &&
		(who.getInfo().y - this -> getY() <= 1 &&
		who.getInfo().y - this -> getY() >= -1)) ||
		((who.getInfo().x - this -> dh -> getX() <= 1 &&
		who.getInfo().x - this -> dh -> getX() >= -1 )&&
		(who.getInfo().y - this -> dh -> getY() <= 1 &&
		who.getInfo().y - this -> dh -> getY() >= -1))){

                Player * pl = dynamic_cast<Player*>(&who);
                if(pl) attack(pl);

	}
}

void Dragon::dieTo(Player * player) {
	//setDisplay('.');
	this -> dh -> isLocked = false;
}

void Dragon::moveTo(int x, int y) {
	return;
}



