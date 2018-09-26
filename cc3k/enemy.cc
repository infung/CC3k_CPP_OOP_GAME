#include "enemy.h"
#include "info.h"
#include "player.h"
#include "iostream"
#include <cstdlib>
#include <cmath>
#include <sstream>
using namespace std;

Enemy::Enemy(int hp, int atk, int def, char c) : Character{hp, atk, def, c} {}

void Enemy::notify(Subject &who) {
	if((who.getInfo().x - this -> getX() <= 1 &&
		who.getInfo().x - this -> getX() >= -1 ) &&
		(who.getInfo().y - this -> getY() <= 1 &&
		who.getInfo().y - this -> getY() >= -1)){
		
		Player * pl = dynamic_cast<Player*>(&who);
		if(pl)
			attack(pl);
//		cout << " and " << getDisplay() << "deals " 
//		<< pl->calculateDamage(getDef(), pl->getAtk()) << " damage to PC"; 
	}
}

int calculateDamage(int att, int def)  {
        return static_cast<int>(ceil((100.0 / (def+100.0)) * att));
}

void Enemy::attack(Player* player) {
	player -> acceptAttack(this);
}

int Enemy::acceptAttack(Player* player) {
	int currHP = this -> getHp();
	int damage = calculateDamage(player -> getAtk(), this -> getDef());
	this -> setHp(currHP - damage);
	if(this -> getHp() <= 0) {
		this -> dieTo(player);
	}
	return damage;	
}

SubscriptionType Enemy::subType() const {
	return SubscriptionType::PlayerToEnemy;
}

void Enemy::dieTo(Player* player) {
	//setDisplay('.');
	srand(time(NULL));
	int num = rand()%2 + 1;
	player -> addGold(num);
	//this -> notifyObservers(SubscriptionType::All);
}

void Enemy::moveTo(int x, int y) {
	setPrevX(getX());
	setPrevY(getY());
	setX(x);
	setY(y);
	this -> notifyObservers(SubscriptionType::All);
}

