#include "troll.h"
#include "enemy.h"
#include <sstream>
#include "merchant.h"

using namespace std;

const int baseHp = 120;
const int baseAtk = 25;
const int baseDef = 15;

Troll::	Troll() :
	Player{baseHp, baseAtk, baseDef, baseHp, 'T'} {}


Troll::~Troll() {}

void Troll::attack(shared_ptr<Enemy> e) {
	if(getHp() > 0){
		int damage = e->acceptAttack(this);
        	 ostringstream ss;
        	if(damage) {
                	ss << "PC deals " << damage << " damage to " << e -> getDisplay()<<"(" << e -> getHp() <<"HP)";
        	} else {
                	ss << "PC missed his attack on " << e -> getDisplay() << "and dealt no damage";
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
		int hp = getHp();
		hp = min(getmaxHp(), hp + 5);
		setHp(hp);
	}
}

void Troll::move(string dir) {
	Character::move(dir);
	int hp = getHp();
	hp = min(getmaxHp(), hp + 5);
	setHp(hp);
}

