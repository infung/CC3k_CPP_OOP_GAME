#include "potion.h"
#include "player.h"
#include "info.h"
#include <iostream>
using namespace std;
unsigned const int HealthPoint = 10;
unsigned const int AtkDef = 5;

string Potion::getType() {return type;}

Potion::Potion(string type) :Item{'P'}, type{type} {}

void Potion::usedBy(Player * player){
	int times = 1;
	if (player->getRace() == 'D') {
		times = 1.5;
 	}
	if(type == "RH") {
		if(player->getmaxHp() - player->getHp() >= HealthPoint) {
			player->setHp(player -> getHp() + times*HealthPoint);
		}
	}else if(type == "BA") {
		player->setAtk(player->getAtk() + times * AtkDef);
	}else if(type == "BD") {
		player->setDef(player->getDef() + times * AtkDef);
	}else if(type == "PH") {
		if(player->getHp() >= HealthPoint) {
			player->setHp(player -> getHp() - times * HealthPoint);
		}
	}else if(type == "WA") {
		if(player->getAtk() >= AtkDef) {
			player->setAtk(player -> getAtk() - times * AtkDef);
		}
	}else if(type == "WD") {
		if(player->getDef() >= AtkDef) {
			player->setDef(player -> getDef() - times * AtkDef);
		}
	}
//	setDisplay('.');
}


Info Potion::getInfo() const {
	return Info{getX(), getY(), getX(), getY(), 'P'};
}

Potion::~Potion() {}


