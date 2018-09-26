#include "elf.h"
#include "player.h"
using namespace std;

Elf::Elf() : Enemy{140, 30, 10, 'E'} {}


void Elf::attack(Player * player) {
	player -> acceptAttack(this);
	if(player -> getHp() > 0)
		player -> acceptAttack(this);
}

