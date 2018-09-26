
#include "halfling.h"
#include "player.h"
using namespace std;

Halfling::Halfling() : Enemy{100, 15, 20, 'L'} {}

int Halfling::acceptAttack(Player* player) {
        srand(time(NULL));
	int miss = rand() % 2;
	if(miss) return 0;
	int currHP = this -> getHp();
        int damage = player -> calculateDamage(player -> getAtk(), this -> getDef());
        this -> setHp(currHP - damage);
        if(this -> getHp() <= 0) {
                this -> dieTo(player);
        }
        return damage;
}


