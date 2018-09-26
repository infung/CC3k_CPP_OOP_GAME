#include "treasure.h"
#include "player.h"
#include <iostream>
#include <sstream>
using namespace std;
int Treasure::getGold() {return gold;}

Treasure::Treasure(int value) : Item{'G'}, gold{value} {}

void Treasure::usedBy(Player * player){
	ostringstream ss;
	ss << "PC picked up " << gold << " gold(s)";
	player -> log(ss.str());
	player->addGold(gold);
	setDisplay('.');
}

Info Treasure::getInfo() const{
	return Info{getX(), getY(), getX(), getY(), 'G'};
}

void Treasure::notify(Subject &who) {

	if(who.getInfo().x == this -> getX() &&
               who.getInfo().y  == this -> getY()  ){
		
		Player *pl = dynamic_cast<Player*>(&who);	
		if(pl)	
			this->usedBy(pl);
	//	cout << " and PC gains golds " << getGold();
	}
	 
}

SubscriptionType Treasure::subType() const {
	return SubscriptionType::PlayerToItem;
}

Treasure::~Treasure() {}

