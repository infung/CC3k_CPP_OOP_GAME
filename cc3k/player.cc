#include <iostream>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include "player.h"
#include "item.h"
#include "enemy.h"
#include "merchant.h"

using namespace std;

Player::Player(int hp, int atk, int def, int maxHp, char race) : 
		Character{hp,atk,def,'@'}, gold{0}, maxHp{maxHp}, race{race} {}

Player::~Player() {}

void Player::attack(shared_ptr<Enemy> e) { 
	int damage = e->acceptAttack(this);
	ostringstream ss;
	if(damage) {
		ss << "PC deals " << damage << " damage to " << e -> getDisplay() <<"(" << e -> getHp() <<"HP)";
	} else {
		ss << "PC missed his attack on " << e -> getDisplay() << " and dealt no damage";
	}
	log(ss.str());
	if(e -> getHp() <= 0){
		ostringstream ss2;
		ss2 << e -> getDisplay() << " died";
		log(ss2.str());
	}
	auto m = dynamic_pointer_cast<Merchant>(e);
        if (m) {
                m->setHostile();
        }
	//if(e -> getHp() <= 0) this -> detach(e);
}

void Player::acceptAttack(Enemy * e) {
	int miss = rand() % 2;
	ostringstream ss;
	if (miss) {
		int damage = calculateDamage(e->getAtk(),getDef());
		setHp(getHp() - damage);
		ss << e -> getDisplay() << " deals " << damage << " damage to PC";
	} else {
		ss << e -> getDisplay() << " missed its attack and dealt no damage to PC";
	}
	log(ss.str());
}

int Player::calculateDamage(int att, int def) const{
	return static_cast<int>(ceil((100.0 / (def+100.0)) * att));
}

void Player::useItem(shared_ptr<Treasure> item) {
	int prevGold = getGold();
	item->usedBy(this);
	ostringstream ss;
	if(getGold() > prevGold) 
		ss << "PC opened a treasure chest and got " << item -> getGold() << " gold";
	log(ss.str());
}

void Player::useItem(shared_ptr<Potion> item) {
	ostringstream ss;
	ss << "PC uses " + item -> getType();
	item -> usedBy(this);
	log(ss.str());
}


int Player::getmaxHp() const {
	return maxHp;
}

void Player::addGold(int val) {
	gold+=val;
}
int Player::getGold() const {
	return gold;
}

char Player::getRace() {return race;}

void Player::log(string str) {
	eventLog.log(str);	
}

void Player::printLog() {
	eventLog.print();
}

