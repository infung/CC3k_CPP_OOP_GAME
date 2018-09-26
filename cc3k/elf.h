#ifndef ELF_H
#define ELF_H
class Subject;
#include "enemy.h"
#include "observer.h"

class Elf: public Enemy{
public:
	Elf();
	void attack(Player * player) override;
};

#endif

