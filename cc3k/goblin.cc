#include "goblin.h"
#include "enemy.h"
#include <sstream>
#include "merchant.h"

using namespace std;
const int baseHp = 110;
const int baseAtk = 15;
const int baseDef = 20;

Goblin::Goblin() :
        Player{baseHp, baseAtk, baseDef, baseHp, 'G'} {}

Goblin::~Goblin() {}

void Goblin::attack(shared_ptr<Enemy> e) {
	int damage = e->acceptAttack(this);
        ostringstream ss;
        if(damage) {
                ss << "PC deals " << damage << " damage to " << e -> getDisplay()<<"(" << e -> getHp() <<"HP)";
        } else {
                ss << "PC missed his attack on " << e -> getDisplay() << "and dealt no damage";
        }
        log(ss.str());
        if (e->getHp() <= 0) {
                addGold(5);
		ss << e -> getDisplay() << " died and PC looted a bonus 5 gold from the corpse of " << e -> getDisplay();
        }
	log(ss.str());
}


void Goblin::acceptAttack(Enemy * e) {
	int miss = rand()%2;
	ostringstream ss;
	if (miss) {
		int damage = calculateDamage(e->getAtk(),getDef());
		if (e->getDisplay() == 'O') {
                        damage *= 1.5;
                }
		setHp(getHp() - damage);
		ss << e -> getDisplay() << " deals " << damage << " damage to PC";
	} else {
		ss << e -> getDisplay() << " missed its attack and dealt no damage to PC";
	}
	log(ss.str());            
}


