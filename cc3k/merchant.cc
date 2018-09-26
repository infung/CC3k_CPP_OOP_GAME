#include "merchant.h"
#include "player.h"
#include <iostream>
#include <sstream>

using namespace std;

bool Merchant::isHostile = false;

Merchant::Merchant() : Enemy{30, 70, 5, 'M'} {}

void Merchant::setHostile() {isHostile = true;}

void Merchant::notify(Subject &who) {
	if(isHostile && ((who.getInfo().x - this -> getX() <= 1 &&
		who.getInfo().x - this -> getX() >= -1 ) &&
		(who.getInfo().y - this -> getY() <= 1 &&
		who.getInfo().y - this -> getY() >= -1))){
		
		Player * pl = dynamic_cast<Player*>(&who);
                if(pl)
                        attack(pl);
		//cout << " and " << getDisplay() << "deals " 
		//<< pl->calculateDamage(getDef(), pl->getAtk()) << " damage to PC"; 
	}
}

void Merchant::dieTo(Player * player) {
}

