#include "vampire.h"
#include <climits>
#include "enemy.h"
#include <sstream>
#include "merchant.h"

using namespace std;

const int baseHp = 50;
const int baseAtk = 25;
const int baseDef = 25;

Vampire::Vampire() :
	Player{baseHp, baseAtk, baseDef, INT_MAX, 'V'} {}


Vampire::~Vampire() {}

void Vampire::attack(shared_ptr<Enemy> e) {
	int damage = e->acceptAttack(this);
         ostringstream ss;
        if(damage) {
		if(e->getDisplay() == 'W') {
			setHp(getHp()-5);
		} else {
			setHp(getHp()+5);
	  	}

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
}


